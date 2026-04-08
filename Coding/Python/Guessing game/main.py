import random
import re

#create a dict
#choose and present number of words
#take user guess
#compare
#count lives

fruits = {"apple":"The colour is red",
          "pineapple":"It makes you itchy in the mouth",
          "banana": "It has lots of potassium",
          "orange":"Taste a little sour"}
fruits_list = list(fruits.keys())
word = random.choice(fruits_list)
hidden_word = re.sub(r'[a-z]', '_', word)
def main():
    correct_guesses = ''
    life = 5

    while True:
        regex_pattern = f"[^{correct_guesses}]" if correct_guesses else (r'[a-z]')
        display_word = re.sub(regex_pattern, '_', word)
        print(display_word)
        print(f"You have {life} lives")
        print(f"Clue: {fruits.get(word)}")
        if "_" not in display_word:
            print("Congrats! You won")
            break

        user_guess = input("Enter your guess: ").lower().strip()

        if user_guess in word:
            print(f'{user_guess} is in the hidden word')
        else:
            life -= 1
        if user_guess not in correct_guesses:
            correct_guesses += user_guess
        else:
            print(f'No, {user_guess} is not in the hidden word')
main()