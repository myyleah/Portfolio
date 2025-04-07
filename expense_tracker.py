import json
import os
import datetime
import matplotlib.pyplot as plt

# Define the file to store expenses and other data
DATA_FILE = 'expense_tracker_data.json'


def load_data():
    """Load data from a file."""
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, 'r') as file:
            return json.load(file)
    return {'expenses': [], 'categories': [], 'budget': {}, 'savings': 0.0, 'savings_goal': 0.0}


def save_data(data):
    """Save data to a file."""
    with open(DATA_FILE, 'w') as file:
        json.dump(data, file, indent=4)


def add_expense(data):
    """Add a new expense."""
    try:
        date = input("Enter the date (YYYY-MM-DD): ")
        amount = float(input("Enter the amount: "))
        category = input("Enter the category: ")
        description = input("Enter a description: ")

        if category not in data['categories']:
            print(f"Category '{category}' does not exist. Please add the category first.")
            return

        expense = {
            'date': date,
            'amount': amount,
            'category': category,
            'description': description
        }
        data['expenses'].append(expense)
        save_data(data)
        print("Expense added successfully!")
    except ValueError:
        print("Invalid input. Please enter the correct data.")


def view_expenses(data):
    """View all expenses."""
    if not data['expenses']:
        print("No expenses recorded yet.")
        return

    for expense in data['expenses']:
        print(f"Date: {expense['date']}, Amount: ${expense['amount']:.2f}, "
              f"Category: {expense['category']}, Description: {expense['description']}")


def delete_expense(data):
    """Delete an expense by its index."""
    view_expenses(data)
    try:
        index = int(input("Enter the index of the expense to delete: ")) - 1
        if 0 <= index < len(data['expenses']):
            del data['expenses'][index]
            save_data(data)
            print("Expense deleted successfully!")
        else:
            print("Invalid index.")
    except ValueError:
        print("Invalid input. Please enter a number.")


def add_category(data):
    """Add a new category."""
    category = input("Enter the new category name: ")
    if category in data['categories']:
        print("Category already exists.")
    else:
        data['categories'].append(category)
        save_data(data)
        print("Category added successfully!")


def set_budget(data):
    """Set a monthly or weekly budget."""
    try:
        budget_type = input("Enter budget type (monthly/weekly): ").lower()
        amount = float(input("Enter the budget amount: "))
        data['budget'][budget_type] = amount
        save_data(data)
        print(f"{budget_type.capitalize()} budget set successfully!")
    except ValueError:
        print("Invalid input. Please enter a correct amount.")


def calculate_total_expenses(expenses):
    """Calculate the total expenses."""
    return sum(expense['amount'] for expense in expenses)


def expenses_by_category(expenses):
    """Calculate expenses by category."""
    category_totals = {}
    for expense in expenses:
        category = expense['category']
        amount = expense['amount']
        if category in category_totals:
            category_totals[category] += amount
        else:
            category_totals[category] = amount
    return category_totals


def generate_report(data):
    """Generate a simple spending report."""
    total_expenses = calculate_total_expenses(data['expenses'])
    category_totals = expenses_by_category(data['expenses'])

    print("\nSpending Report")
    print(f"Total Expenses: ${total_expenses:.2f}")
    print("Expenses by Category:")
    for category, total in category_totals.items():
        print(f"{category}: ${total:.2f}")


def calculate_budget(data):
    """Calculate the remaining budget."""
    total_expenses = calculate_total_expenses(data['expenses'])
    current_date = datetime.datetime.now()
    if 'monthly' in data['budget']:
        budget = data['budget']['monthly']
        days_in_month = (current_date.replace(month=current_date.month % 12 + 1, day=1) - datetime.timedelta(days=1)).day
        days_passed = current_date.day
        budget_left = budget - (total_expenses / days_passed * days_in_month)
        print(f"Monthly budget left: ${budget_left:.2f}")
    if 'weekly' in data['budget']:
        budget = data['budget']['weekly']
        week_day = current_date.weekday() + 1
        budget_left = budget - (total_expenses / week_day * 7)
        print(f"Weekly budget left: ${budget_left:.2f}")


def add_savings(data):
    """Add savings."""
    try:
        amount = float(input("Enter the amount to add to savings: "))
        data['savings'] += amount
        save_data(data)
        print("Savings added successfully!")
    except ValueError:
        print("Invalid input. Please enter a correct amount.")


def set_savings_goal(data):
    """Set a savings goal."""
    try:
        goal = float(input("Enter your savings goal: "))
        data['savings_goal'] = goal
        save_data(data)
        print("Savings goal set successfully!")
    except ValueError:
        print("Invalid input. Please enter a correct amount.")


def view_savings(data):
    """View savings and progress towards savings goal."""
    print(f"Total Savings: ${data['savings']:.2f}")
    if data['savings_goal'] > 0:
        progress = (data['savings'] / data['savings_goal']) * 100
        print(f"Savings Goal: ${data['savings_goal']:.2f}")
        print(f"Progress: {progress:.2f}%")


def plot_expenses_by_category(data):
    """Plot expenses by category."""
    category_totals = expenses_by_category(data['expenses'])
    categories = list(category_totals.keys())
    totals = list(category_totals.values())

    plt.figure(figsize=(10, 5))
    plt.bar(categories, totals, color='blue')
    plt.xlabel('Category')
    plt.ylabel('Total Expenses')
    plt.title('Expenses by Category')
    plt.show()


def main():
    data = load_data()

    while True:
        print("\nPersonal Expense Tracker")
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. Delete Expense")
        print("4. Add Category")
        print("5. Set Budget")
        print("6. Generate Report")
        print("7. Calculate Budget Left")
        print("8. Add Savings")
        print("9. Set Savings Goal")
        print("10. View Savings")
        print("11. Plot Expenses by Category")
        print("12. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            add_expense(data)
        elif choice == '2':
            view_expenses(data)
        elif choice == '3':
            delete_expense(data)
        elif choice == '4':
            add_category(data)
        elif choice == '5':
            set_budget(data)
        elif choice == '6':
            generate_report(data)
        elif choice == '7':
            calculate_budget(data)
        elif choice == '8':
            add_savings(data)
        elif choice == '9':
            set_savings_goal(data)
        elif choice == '10':
            view_savings(data)
        elif choice == '11':
            plot_expenses_by_category(data)
        elif choice == '12':
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()
