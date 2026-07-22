import random
import re

#create wordlist
wordlist_stationary = ['marker', 'pencil', 'pen', 'ruler', 'eraser']
wordlist_vehicle = ['car', 'van', 'aeroplane', 'yacht', 'train']
#pick wordlist
def word_stationary():
    return random.choice(wordlist_stationary)

def word_vehicle():
    return random.choice(wordlist_vehicle)
#ask for input
def choice():
    print('Available categories: Vehicle  Stationary')
    categories = input('What category do you want to play: ').strip().lower()
    if categories == 'vehicle':
        secret_word = word_vehicle()
        main(secret_word)
    elif categories == 'stationary':
        secret_word = word_stationary()
        main(secret_word)
    else:
        print(f'{categories} is not a valid categories')
        choice()

def main(secret):
    print('You have 5 lives')
    live = 5
    correct_word = ''
    new_word = re.sub(r'.', '_', secret)
    secret_wrd = re.sub(r'.', '_', secret)
    print(secret_wrd)
    while True:
        guess = input('Guess an alphabet: ').strip().lower()
        if len(guess) == 1:
            if guess in secret:
                print(f'{guess} is in secret word')
                correct_word += guess
                new_word = re.sub(f'[^{correct_word}]', '_', secret)
                print(new_word)
                if new_word == secret:
                    print('Congrats, you win!')
                    break
            else:
                print(f'{guess} is not in secret word')
                live -= 1
                print(f'{live} lives left')
                print(new_word)
                if live == 0:
                    print('You lose. Try again next time')
                    print(f'The secret word is {secret}')
                    break
        else:
            print('Please enter a valid guess')
start = '1'
#create greeting
while start == '1':
    print('--------Welcome to a hangman game--------')
    play = input('\nDo you want to play a hangman game? (y/n): ').strip().lower()
    if play == 'y':
        choice()
        break
    elif play == 'n':
        print('Bye bye')
        break
    else:
        print(f'{play} is not a valid answer')
        start = '1'

#change the word and lives according to input
