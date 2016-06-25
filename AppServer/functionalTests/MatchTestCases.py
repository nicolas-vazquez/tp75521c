import requests
import unittest
import json
import uuid
import ConfigParser

class MatchTest(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(MatchTest, self).__init__(*args, **kwargs)

	@classmethod
	def setUpClass(cls):
		cls.__api_base_url = "http://localhost:8083/"
		cls._url_usuario = "api/accounts/"
		cls._url_matches = "api/matches/"
		cls._username_long = uuid.uuid4().hex
		cls._username = cls._username_long[0:10]
		

	def test_1(self):
		payload= {'username': self._username  , 'password': 'pass', 'name': 'name', 'age': 20, 'gender':'M', 'email':'email@email.com', 'latitude': '-34.58', 'longitude': '-58.60', 'photo_profile':'AAA'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 200)


	#Bad credentials matches list	
	def test_2(self):
		r = requests.get(self.__api_base_url + self._url_matches)
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials candidates list	
	def test_3(self):
		r = requests.get(self.__api_base_url + self._url_matches + "candidates")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials messages from user	
	def test_4(self):
		chatID = "user1+user2"
		r = requests.get(self.__api_base_url + self._url_matches +  chatID + "/messages")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials message to user	
	def test_5(self):
		chatID = "user1+user2"
		r = requests.post(self.__api_base_url + self._url_matches +  chatID + "/message")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Successful matches list 	
	def test_6(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		token = data["data"]["accessToken"]

		payload = {'Authorization': token}
		r = requests.get(self.__api_base_url + self._url_matches, headers=payload)
		self.assertEqual(r.status_code, 200)

	#Successful candidates list	 
	def test_7(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		token = data["data"]["accessToken"]

		payload = {'Authorization': token}
		query={'radius':100,'latitude':'-34.6129','longitude':'-58.3859'}
		r = requests.get(self.__api_base_url + self._url_matches + "candidates", headers=payload, params=query)

		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertTrue(data)

	#No chatID found
	def test_8(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		token = data["data"]["accessToken"]

		payload = {'Authorization': token}
		chatID = "user1+user2"
		r = requests.get(self.__api_base_url + self._url_matches +  chatID + "/messages", headers=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["message"], "Resource not found")

	#No chatID found
	def test_9(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		token = data["data"]["accessToken"]
		header = {'Authorization': token }
		payload={'message':'A message'}
		chatID = "user1+user2"
		r = requests.post(self.__api_base_url + self._url_matches +  chatID + "/message", headers=header,json=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["message"], "Resource not found")
