from survey import AnonymousSurvey as AS

question = 'What is your favourite song'
survey = AS(question)

survey.show_question()
print('Enter q to quit any time.\n')
while True:
    response = input('Song: ').lower().strip()
    if response == 'q':
        break
    survey.store_response(response)

print('Thank you to everyone who participated in this survey.\n')
survey.show_results()