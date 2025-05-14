from utils import *
from datetime import datetime
import calendar
from states import *

###################################################
# Revenue = Price * Quanity * (1+state tax rate)  #
# Gross Profit = (Price - Cost) * Quanity         #
# Net Profit = Gross Profit - Expenses            #
###################################################

def calculate_all_data(all_sales, products, expenses, tax_rates, customers):

    customer_records = {k: v for k, v in customers.items() if isinstance(v,dict)}
    monthly_data = {}
    product_data = {}

    total_customers = len(customer_records)
    swapped_count = customers.get("SwappedCount", 0)

    stats = {
        "FirstName": sum(1 for c in customer_records.values() if c["FirstName"] == "") / total_customers * 100,
        "LastName": sum(1 for c in customer_records.values() if c["LastName"] == "") / total_customers * 100,
        "Zip": sum(1 for c in customer_records.values() if c["Zip"] == "") / total_customers * 100,
        "State": sum(1 for c in customer_records.values() if c["State"] == "") / total_customers * 100,
        "Zip and State": customers.get("SwappedCount",0) / total_customers * 100,
    }

    # Iterate through sales data.
    for sale in all_sales:
        product_id = sale["ProductId"]
        customer_id = sale["CustomerId"]
        quantity = int(sale["Quantity"])
        date = sale["Date"]
        state = customers.get(customer_id, {}).get("State", "")
        state_full = us_states.get(state.upper(), state.title())

        if state_full in tax_rates:
            state_rate = tax_rates[state_full]["Rate"]
        else:
            state_rate = 0.0

        month = calendar.month_name[int(datetime.strptime(date, "%Y-%m-%d").strftime("%m"))]

        price = float(products[product_id]["Price"])
        cost = float(products[product_id]["Cost"])

        revenue = price * quantity * (1 + state_rate)
        gross_profit = (price - cost) * quantity

        # Initialize monthly data if not already present
        if month not in monthly_data:
            monthly_data[month] = {"Revenue": 0, "GrossProfit": 0, "NetProfit": 0}

        # Aggregate monthly data
        monthly_data[month]["Revenue"] += revenue
        monthly_data[month]["GrossProfit"] += gross_profit

        # Initialize product data if not already present
        if product_id not in product_data:
            product_data[product_id] = {"Revenue": 0, "Quantity": 0, "GrossProfit": 0}

        # Aggregate product data
        product_data[product_id]["Revenue"] += revenue
        product_data[product_id]["Quantity"] += quantity
        product_data[product_id]["GrossProfit"] += gross_profit

    # Handle expenses
    for month,expense in expenses.items():
        if expense["Month"] == '':
            continue
        else:
            monthValue = calendar.month_name[int(expense["Month"])]

        if monthValue in monthly_data:
            monthly_data[monthValue]["NetProfit"] = (
                monthly_data[monthValue]["GrossProfit"] - float(expense["Expenses"])
            )
        else:
            monthly_data[monthValue] = {"Revenue": 0, "GrossProfit": 0, "NetProfit": -float(expense["Expenses"])}

    return product_data, monthly_data, stats

# Start of main function: Calling all utils and flattening monthly_sales
tax_rates = get_tax()
expenses = get_expenses()
products = get_products()
all_sales = get_monthly_sales()
monthly_sales = [sale for sales_month in all_sales for sale in sales_month]

# Calling main function and placing data into dicts for calling later.
product_data, monthly_sales_data, customers = calculate_all_data(monthly_sales, products, expenses, tax_rates, get_customers(clean_data=True))
for field, percentage in customers.items():
    if field == "Zip and State":
        print(f'{percentage:.2f} % swapped "State" and "Zip" fields')
    else:
        print(f'{percentage:.2f} % missing "{field}" fields.')

# Get my min max data (there is 100% a better way of doing this, I just tried to and it broke)
max_revenue_month = max(monthly_sales_data, key=lambda m: monthly_sales_data[m]["Revenue"])
min_revenue_month = min(monthly_sales_data, key=lambda m: monthly_sales_data[m]["Revenue"])
max_gross_month = max(monthly_sales_data, key=lambda m: monthly_sales_data[m]["GrossProfit"])
min_gross_month = min(monthly_sales_data, key=lambda m: monthly_sales_data[m]["GrossProfit"])
max_net_month = max(monthly_sales_data, key=lambda m: monthly_sales_data[m]["NetProfit"])
min_net_month = min(monthly_sales_data, key=lambda m: monthly_sales_data[m]["NetProfit"])

most_revenue_product = max(product_data, key=lambda p: product_data[p]["Revenue"])
least_revenue_product = min(product_data, key=lambda p: product_data[p]["Revenue"])
best_selling_product = max(product_data, key=lambda p: product_data[p]["Quantity"])
worst_selling_product = min(product_data, key=lambda p: product_data[p]["Quantity"])
most_profitable_product = max(product_data, key=lambda p: product_data[p]["GrossProfit"])
least_profitable_product = min(product_data, key=lambda p: product_data[p]["GrossProfit"])

# Lots of prints
print(f"{max_revenue_month} had the most revenue with ${monthly_sales_data[max_revenue_month]['Revenue']:,.2f}.")
print(f"{max_gross_month} had the most gross profit with ${monthly_sales_data[max_gross_month]['GrossProfit']:,.2f}.")
print(f"{max_net_month} had the most net profit with ${monthly_sales_data[max_net_month]['NetProfit']:,.2f}.")
print(f"{min_revenue_month} had the least revenue with ${monthly_sales_data[min_revenue_month]['Revenue']:,.2f}.")
print(f"{min_gross_month} had the least gross profit with ${monthly_sales_data[min_gross_month]['GrossProfit']:,.2f}.")
print(f"{min_net_month} had the least net profit with ${monthly_sales_data[min_net_month]['NetProfit']:,.2f}.")

print(f'The "{most_revenue_product}" had the most annual revenue with $ {product_data[most_revenue_product]["Revenue"]:,.2f}.')
print(f'The "{best_selling_product}" sold the most units with {product_data[best_selling_product]["Quantity"]:,}.')
print(f'The "{most_profitable_product}" had the most annual gross profit with $ {product_data[most_profitable_product]["GrossProfit"]:,.2f}.')
print(f'The "{least_revenue_product}" had the least annual revenue with $ {product_data[least_revenue_product]["Revenue"]:,.2f}.')
print(f'The "{worst_selling_product}" sold the least units with {product_data[worst_selling_product]["Quantity"]:,}.')
print(f'The "{least_profitable_product}" had the least annual gross profit with $ {product_data[least_profitable_product]["GrossProfit"]:,.2f}.')
