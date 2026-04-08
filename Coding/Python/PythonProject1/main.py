import random as r

game_list = ['rock','paper','scissor']



print('We will play 10 game nigga')
for i in range(1, 11):
    comp_choice = r.choice(game_list)
    user_choice = input('Enter your choice (rock,paper,scissor):').strip().lower()
    print(f'Your move: {user_choice}\nComputer move: {comp_choice}')

    if user_choice == 'rock' and comp_choice == 'paper':
        print('You lose nigger')
    elif user_choice == 'paper' and comp_choice == 'scissor':
        print('You lose nigger')
    elif user_choice == 'scissor' and comp_choice == 'rock':
        print('You lose nigger')
    else:
        print('Maybe you win but do you think you are tough buddy')
