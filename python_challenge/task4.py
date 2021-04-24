import requests

url = "http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing="
number = "631"
for i in range(100):
    r = requests.get(url+number)
    print(r.text, end="\t")
    str = r.text
    number = str[-5:]
    print(number)
print("HI!")
