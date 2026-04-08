import random

possible_int = [*range(1,10)]
possible_thing = [*range(1,10),'!','@','#','$','%','^','&','*','/','?','_','-','.']

def random_password_generator():
    length = int(input("How long do you want your password to be:"))
    special_character = input("Do you want special characters inside your password (Y/N):").upper()

    if special_character == "Y":
        list_generated = (random.choices(possible_thing, k=length))
        list_int_generated = [str(num) for num in list_generated]
        print(f"Your generated password is:{"".join(list_int_generated)}")
    elif special_character == "N":
        list_generated = (random.choices(possible_int, k=length))
        list_int_generated = [str(num) for num in list_generated]
        print(f"Your generated password is:{"".join(list_int_generated)}")

random_password_generator()