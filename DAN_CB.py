# FINAL DAN
#%%
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
from torch.nn.utils import clip_grad_norm_
from torch.nn.utils.rnn import pad_sequence

from datasets import load_dataset

from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score

import nltk
import numpy as np
import json
import time
from torchmetrics import F1Score
from torchmetrics.classification import MulticlassAccuracy, MulticlassF1Score

from transformers import AutoTokenizer
tokenizer = AutoTokenizer.from_pretrained("distilbert-base-uncased", return_tensors='pt', truncation_side='left')

kUNK = '<unk>'
kPAD = '<pad>'

dataset = load_dataset('cbt', 'CN', split='train[:10000]')
dataset = dataset.train_test_split(test_size=0.2)


# Preprocessing
def preprocess_function(examples) :
    contexts = [["".join(sentence)]*10 for sentence in examples["sentences"]] # list of sentences
    questions = [question for question in examples['question']]

    options = [option for option in examples['options']] # list of list
    questions = [[questions[idx].replace("XXXXX", option) for option in options] for idx, options in enumerate(options)]

    answers = examples['answer']
    labels = [options[idx].index(answer) for idx, answer in enumerate(answers)]

    contexts = sum(contexts, [])
    questions = sum(questions, [])

    tokenized_examples = tokenizer(contexts, questions, truncation="only_first", max_length=256, 
                                   return_tensors='pt', padding=True)

    tokenized_examples = {k: [v[i : i + 10] for i in range(0, len(v), 10)] for k, v in tokenized_examples.items()}

    # def make_onehot(label) :
    #     answer = [0]*10
    #     answer[label] = 1
    #     return answer

    # tokenized_examples['label'] = [make_onehot(label) for label in labels]

    tokenized_examples['label'] = labels
    return tokenized_examples

#%%
vocab_size = tokenizer.vocab_size
cbt_choice = 10

#%%
class DanModel(nn.Module):

    def __init__(self, n_classes=cbt_choice, vocab_size=vocab_size, emb_dim=1000,
                 n_hidden_units=1000, nn_dropout=.5):
        super(DanModel, self).__init__()
        self.n_classes = n_classes
        self.vocab_size = vocab_size
        self.emb_dim = emb_dim
        self.n_hidden_units = n_hidden_units
        self.nn_dropout = nn_dropout
        self.embeddings = nn.Embedding(self.vocab_size, self.emb_dim, padding_idx=0)
        self.linear1 = nn.Linear(emb_dim, n_hidden_units)
        self.linear2 = nn.Linear(n_hidden_units, n_classes)
        self.linear3 = nn.Linear(n_classes*n_classes, n_classes)

        self.classifier = nn.Sequential(self.linear1,
                                        nn.ReLU(),
                                        
                                        self.linear2)
        self._softmax = nn.Softmax()
       
    def forward(self, input_text, is_prob=False):

        # logits = torch.LongTensor([0.0] * self.n_classes)
        text_embeddings = self.embeddings(input_text)
        encoded = text_embeddings.mean(axis=2)
        logits = self.classifier(encoded)
        logits = logits.reshape(-1, 100)
        logits = self._softmax(logits)
        logits = self.linear3(logits)
        # logits = logits.mean(axis=1)
        
        # # if is_prob:
        logits = self._softmax(logits)
        # return logits
        return logits

        # return logits
#%%

tokenized_dataset = dataset.map(preprocess_function, batched=True)
tokenized_dataset.set_format(type='torch', columns=['input_ids', 'label'])

train_dataloader = torch.utils.data.DataLoader(tokenized_dataset['train'], batch_size=32)
test_dataloader = torch.utils.data.DataLoader(tokenized_dataset['test'], batch_size=32)

# #%%
# for batch in train_dataloader:
#     batch
    
#     break
# #%%
# x = batch['input_ids']
# y = batch['label']
# model = DanModel()
# pred = model(x)
# #%%


# #%%
# f1_score(pred, y)
# #%%
# pred

# #%%
# len(x)



#%%
def evaluate(data_loader, model, device):
    """
    evaluate the current model, get the accuracy for dev/test set
    Keyword arguments:
    data_loader: pytorch build-in data loader output
    model: model to be evaluated
    device: cpu of gpu
    """

    acc_score = MulticlassAccuracy(10).to(device)
    f1_score = MulticlassF1Score(10, average='macro').to(device)

    model.eval()
    num_examples = 0
    error = 0
    f1 = 0
    acc = 0

    for idx, batch in enumerate(data_loader):
        question_text = batch['input_ids'].to(device)
        sample_size = len(question_text)
        # question_len = batch['len']
        labels = batch['label'].to(device)
        logits = model.forward(question_text)

        # top_n, top_i = logits.topk(1)
        num_examples += question_text.size(0)
        # error += torch.nonzero(top_i.squeeze() - torch.LongTensor(labels)).size(0)
        acc += acc_score(logits, labels) * sample_size
        f1 += f1_score(logits, labels) * sample_size
    
    #-- also calculate f1 score

    # accuracy = 1 - error / num_examples
    acc = acc / num_examples
    f1 = f1/ num_examples
    print('accuracy : ', acc.item())
    print('f1 score : ', f1.item())
    return acc

def train(save_path, checkpoint, model, train_data_loader, dev_data_loader, accuracy, device):
    """
    Train the current model
    Keyword arguments:
    args: arguments 
    model: model to be trained
    train_data_loader: pytorch build-in data loader output for training examples
    dev_data_loader: pytorch build-in data loader output for dev examples
    accuracy: previous best accuracy
    device: cpu of gpu
    """

    model.train()
    optimizer = torch.optim.Adamax(model.parameters())
    criterion = nn.CrossEntropyLoss()
    print_loss_total = 0
    epoch_loss_total = 0
    start = time.time()

    for idx, batch in enumerate(train_data_loader):
        question_text = batch['input_ids'].to(device)
        # question_len = batch['len']
        labels = batch['label'].to(device)

        model.zero_grad()
        pred = model(question_text)
        loss = criterion(pred, labels)
        loss.backward()
        optimizer.step()

        # clip_grad_norm_(model.parameters(), args.grad_clipping) 
        print_loss_total += loss.data.cpu().numpy()
        epoch_loss_total += loss.data.cpu().numpy()

        if idx % checkpoint == 0 and idx > 0:
            print_loss_avg = print_loss_total / checkpoint

            print('number of steps: %d, loss: %.5f time: %.5f' % (idx, print_loss_avg, time.time()- start))
            print_loss_total = 0
            curr_accuracy = evaluate(dev_data_loader, model, device)
            if accuracy < curr_accuracy:
                torch.save(model, save_path)
                accuracy = curr_accuracy
    return accuracy, model

device = 'cuda' if torch.cuda.is_available() else 'cpu'
dan_model = DanModel()
dan_model.to(device)

import os  
os.makedirs("./model/", exist_ok=True)
save_path = './model/dan_model.pth'


accuracy, dan_model = train(save_path, 5, dan_model, train_dataloader, test_dataloader, 0, device)
torch.save(dan_model.state_dict(), "./model/dan_model.pth")
