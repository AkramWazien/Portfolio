import random

questions = {"What is 3 + 2":"5",
             "What is 5 - 10":"-5",
             "What is 2 x 7":"14",
             "What is 9 / 3":"3",
             "What is 6 + 7":"13"}

def trivia_game():
    question_list = list(questions.keys())
    total_need = 3

    questions_picked = random.sample(question_list, total_need)
    score = 0
    for idx, question in enumerate(questions_picked):
        print(f"{idx + 1}.{question}")
        ans = input(":")
        if ans == questions.get(question):
            print(f"Congrats,{ans} is correct")
            score += 1
            print(f"Your score is {score}")
        else:
            print(f"Sorry,{ans} is incorrect\n"
                  f"The answer is {questions.get(question)}")
            score = score
            print(f"Your score is {score}")
trivia_game()