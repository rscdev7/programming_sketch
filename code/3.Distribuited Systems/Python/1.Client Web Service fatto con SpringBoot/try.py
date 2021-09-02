import requests
import json

#GET CON PARAMETRO OK
payload =  {'id':'56'
}
headers = {'content-type': 'application/json'}
risp=requests.get("http://localhost:8080/api/exams/",payload)
print (risp.text)

"""
#PUT NON VA
payload =  {'id':'5','description': 'aaaaa','date':'2019-09-09'}
headers = {'content-type': 'application/json'}
risp=requests.put("http://localhost:8080/api/exams/",data=json.dumps(payload),headers=headers)
print (risp)
"""

#POST NON VA
payload =  { "description": "Analisi 1",
"date": "2019-02-01T15:00:00+0100"
}
headers = {'content-type': 'application/json'}
risp=requests.post("http://localhost:8080/api/exams/",data=json.dumps(payload),headers=headers)
print (risp.text)

#DELETE FUNZIONA
risp=requests.delete("http://localhost:8080/api/exams/10")
print (risp)

#GET SENZA PARAMETRO FUNZIONA
risp=requests.get("http://localhost:8080/api/exams/")
print (risp.text)
