from bs4 import BeautifulSoup as bs
import requests
import json
datas = []

html_text = requests.get(url='https://books.toscrape.com/catalogue/category/books/fiction_10/index.html').text
html_text.encode('utf-8').decode('utf-8')
soup = bs(html_text, 'html.parser')
products = soup.find_all('article', class_="product_pod")

for book in products:
    if book.find('p', class_='star-rating Five'):
        title = book.h3.a['title']
        
        price_product = book.find('div', class_='product_price')
        if price_product:
            price = price_product.find('p', class_='price_color').text

            data = {
                'title': title,
                'price': price,
            }
            datas.append(data)

with open('data.json', 'w') as json_data:
    json.dump(datas, json_data, indent=4)