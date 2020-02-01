from urllib.request import urlopen
from bs4 import BeautifulSoup
import requests

url = input("Enter a website to extract the links from:")

#In case of wrong URL
try:
	page = urlopen(url)
except:
	print("Error opening the URL")

soup = BeautifulSoup(page, 'html.parser')

content = soup.find('div', {"class": "story-body sp-story-body gel-body-copy"})

#iterate through content to find <p>
article = ''
for i in content.findAll('p'):
	article = article + '' + i.text

with open('scraped_text.txt', 'w') as file:
	file.write(article)
