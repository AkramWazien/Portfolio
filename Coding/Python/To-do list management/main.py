import json

#load task
#view task
#create task
#remove task
#save task
#mark as complete
#mark as incomplete
#exit

file_name = "to_do_list.json"

def view_task(tasks):
   task_list = tasks["tasks"]
   if len(task_list) == 0:
       print("No tasks to display")
   else:
       print('Your task is:')
       for idx, task in enumerate(task_list):
           status = "[Completed]" if task.get("complete") else "[Pending]"
           print(f'{idx + 1}. {task.get("description")}|{status}')

def create_task(tasks):
    description = input("Enter the task description:").strip()
    if description:
        tasks["tasks"].append({"description": description , "complete": False})
        save_task(tasks)
        print("Task is saved")
    else:
        print("Description cannot be empty.")
def load_task():
    try:
        with open(file_name, 'r') as file:
            return json.load(file)
    except:
        return {"tasks": []}

def save_task(tasks):
    try:
        with open(file_name,"w") as file:
            json.dump(tasks, file)
    except:
        print("File failed to save")

def mark_complete(tasks):
    view_task(tasks)
    number_chosen = int(input("Which task do you want to mark as complete:"))
    task_list = tasks["tasks"]
    try:
        if 1 <= number_chosen <= len(task_list):
            tasks["tasks"][number_chosen - 1]["complete"] = True
            save_task(tasks)
            print("Task is completed")

        else:
            print(f"{number_chosen} is invalid")

    except:
        print("Number is invalid")

def mark_incomplete(tasks):
    view_task(tasks)
    number_chosen = int(input("Which task do you want to mark as pending:"))
    task_list = tasks["tasks"]
    try:
        if 1 <= number_chosen <= len(task_list):
            tasks["tasks"][number_chosen - 1]["complete"] = False
            save_task(tasks)
            print("Task is pending")

        else:
            print(f"{number_chosen} is invalid")

    except:
        print("Number is invalid")

def remove_task(tasks):
    view_task(tasks)
    number_chosen = int(input("Which task do you want to remove:"))
    task_list = tasks["tasks"]
    print(number_chosen - 1)
    print(task_list)
    print(len(task_list))
    try:
        if 1 <= number_chosen <= len(task_list):
            task_list.pop(number_chosen - 1)
            save_task(tasks)
            print("Task is removed")

        else:
            print(f"{number_chosen} is invalid")
    except:
        print("Number is invalid")

def clear_all(tasks):
    tasks['tasks'] = []
    print("All tasks is cleared")

def main():
    tasks =  load_task()
    while True:
        print("To-do list\n")
        print("1. View tasks")
        print("2. Create tasks")
        print("3. Mark task as complete")
        print("4. Mark task as pending")
        print("5. Remove task")
        print("6. Clear all")
        print("7. Exit")

        choice = int(input("What do you want to do: ").strip())
        print("")
        if choice == 1:
            view_task(tasks)
        elif choice == 2:
            create_task(tasks)
        elif choice == 3:
            mark_complete(tasks)
        elif choice == 4:
            mark_incomplete(tasks)
        elif choice == 5:
            remove_task(tasks)
        elif choice == 6:
            clear_all(tasks)
        elif choice == 7:
            print("Thank you. Goodbye\n")
            break
        else:
            print(f"Sorry,{choice} is not valid. Please try again")

main()