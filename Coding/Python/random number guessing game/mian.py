import random

def guessing_game():
    i = 1
    score = 0
    print("Welcome to a random number guessing game!\n"
          "I hope you will have a lot of fun")
    while i == 1:
        random_number = random.randint(1, 2)

        print("Choose any number between 1 and 2")
        user_answer = str(input("Please enter your guess:"))
        if user_answer == str(random_number):
            i = 1
            score += 1
            print("Congrats, your answer is correct\n"
                  f"Your score is {score}")

        else:
            print(f"Sorry, {user_answer} is not correct\n"
                  f"The correct answer is {random_number}\n"
                  f"Your score is {score}")
            i = 0

guessing_game()