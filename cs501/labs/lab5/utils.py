import urllib.request
import os
from states import *

def download_data():
    path_prefix = "data/"

    if not os.path.isdir(path_prefix):
        os.mkdir(path_prefix)

    url_prefix ="https://cs.indstate.edu/~mjavaid1/sales-data/"

    files = [
        "customers",
        "products",
        "tax",
        "expenses",
    ]

    files = files + [f"sales-{i:0>2}" for i in range(1,13)]

    for file in files:
        with urllib.request.urlopen(f"{url_prefix}{file}.csv") as req:
           data = req.read().decode("utf-8")
        
        with open(f"{path_prefix}{file}.csv","w") as f:
           f.write(data)

row_sep="\n"
url_prefix ="https://cs.indstate.edu/~mjavaid1/sales-data/" 

def read_csv(uri, col_sep=",",row_sep="\n",primary_key=None):
        if os.path.isfile(uri):
            with open(uri,"r") as f:
                data=f.read()
        else:
            with urllib.request.urlopen(f"{url_prefix}{uri}.csv") as req:
                data = req.read().decode("utf-8") # such as when the URL is passed as part of a request or response in a binary format, or if it's encoded in a specific character set or URL encoding format.

        lines=data.strip().split(row_sep) #Removes spaces at beginning or end of string
        lines=[line.strip().split(col_sep) for line in lines if line.strip() != ""] #line of lines
        titles=lines[0]
#            print(lines[0][0])
        records = lines[1:]

        if not primary_key:
                return [{titles[i]:record[i] for i in range(len(titles))} for record in records]
            
        return {record[titles.index(primary_key)]:
                {titles[i]:record[i] for i in range(len(titles))} for record in records}

#download_data()
def clean_customers(customers):
    swapped_count = 0
    for k in customers.keys():
        customer=customers[k]
        if customer["State"].isdigit() and customer["Zip"].isalpha():
            tmp=customer["State"]
            customer["State"]=customer["Zip"]
            customer["Zip"]=tmp
            swapped_count += 1
    customers["SwappedCount"] = swapped_count
    return customers

def get_customers(clean_data=True):
    records = read_csv("customers",primary_key="CustomerId")
    if not clean_data:
        return records
    return clean_customers(records)
     

def get_tax():
    records=read_csv("tax",primary_key="State")
    return clean_tax(records)
 #   return records

def clean_tax(tax_rates):
    for k in tax_rates.keys():
        tax_rate = tax_rates[k]
        del tax_rate["Rank"]
        if tax_rate["Rate"]=="N/A":
            tax_rate["Rate"]=0.0
        else:
            tax_rate["Rate"]= float(tax_rate["Rate"].strip("%"))/100
    tax_rates[""]= {'State':"", 'Rate':0.0}
    return tax_rates

def get_products():
    return read_csv("products",primary_key="ProductId")

def get_expenses():
    expenses = read_csv("expenses",primary_key="Month")
    expenses[""]={'Month':"",'Expenses':0.0}
    return expenses

def get_monthly_sales():# list of list of dictionaries
    return [read_csv(f"sales-{i:0>2}") for i in range(1,13)]

all_sales=get_monthly_sales() #list of list
products=get_products()
customers=get_customers(clean_data=False)
customers_cd=get_customers()
taxes=get_tax()
expenses=get_expenses()

