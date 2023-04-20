# COPYRIGHT 2023 MATT SERDUKOFF
# PYTHON VERSION 2.7.18 and PANDAS VERSION 0.24.2
import pandas as pd

# read in excel file
df = pd.read_csv('train.csv')

# dictionary for score for each word/term
score_counts = {}

# counter for debugging
line_num = 0

# loop through dataframe
for index, row in df.iterrows():
    line_num += 1
    anchor_word = row['anchor']
    score = row['score']
    # if word is not in 'score_counts' add it with score and count of 1
    if anchor_word not in score_counts:
        score_counts[anchor_word] = {'score': score, 'count': 1}
    # if word already is in 'score_counts', update the count and score
    else:
        score_counts[anchor_word]['score'] += score
        score_counts[anchor_word]['count'] += 1
    # this is just to show that the program does go through all ~37,000 lines.
    print("Processing line " + str(line_num) + "...")

# dictionary for average word
avg_scores = {}

# loop through each word
for anchor_word in score_counts:
    # calculate average for each word in loop
    avg_score = score_counts[anchor_word]['score'] / score_counts[anchor_word]['count']
    # store average in avg_scores
    avg_scores[anchor_word] = {'score': avg_score, 'count': score_counts[anchor_word]['count']}

# sort the avg_scores dictionary by score in descending order
sorted_avg_scores = sorted(avg_scores.items(), key=lambda x: x[1]['score'], reverse=True)

# print the top five words with the highest average score
print("The top five anchor words with the highest average score are:")
for i in range(5):
    anchor_word = sorted_avg_scores[i][0]
    avg_score = sorted_avg_scores[i][1]['score']
    count = sorted_avg_scores[i][1]['count']
    print("{0}: {1:.2f} ({2} instances)".format(anchor_word, avg_score, count))

print('\n\nThis also program allows you to see the data in a customized manner.')
print('You may decide to only select words with higher than a certain amount of instances for statistical significance.')

# count how many instances user wants to filter with
instances = input('Select what instance threshold you would like. Ex:10, or press 0 to exit.')

# counter to count how many terms are displayed
i = input('How many terms do you want to see?\n')

if instances == 0:
    exit()
else:
    results = pd.DataFrame(columns=['anchor', 'avg_score', 'count'])

    # loop through each unique anchor word
    for anchor_word in df['anchor'].unique():
    
        # filter the DataFrame to only include rows with the current anchor word
        anchor_df = df[df['anchor'] == anchor_word]
    
        # calculate the average score and count for the current anchor word
        avg_score = anchor_df['score'].mean()
        count = len(anchor_df)
    
        # add the results to the new DataFrame
        results = results.append({'anchor': anchor_word, 'avg_score': avg_score, 'count': count}, ignore_index=True)

    # sort the results by average score in descending order
    results = results.sort_values(by='avg_score', ascending=False)

    # display the top ten anchor words with more than 10 instances
    top_ten = results[results['count'] > instances].head(i)
    for index, row in top_ten.iterrows():
        print("The anchor word with the highest average score (out of {} instances) is '{}' with an average score of {}."
            .format(row['count'], row['anchor'], row['avg_score']))

