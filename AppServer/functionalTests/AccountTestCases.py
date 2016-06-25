import requests
import unittest
import json
import uuid
import ConfigParser

class AccountTest(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(AccountTest, self).__init__(*args, **kwargs)
		self.__api_base_url = "http://localhost:8083/"
		self._url_usuario = "api/accounts/"

	@classmethod
	def setUpClass(cls):
		cls._username_long = uuid.uuid4().hex
		cls._username = cls._username_long[0:10]		
		cls._usernamelike = cls._username + "like"

	#Successful signup
	def test_1(self):
		payload= {'username': self._username, 'password': 'pass', 'name': 'name', 'age': 20, 'gender':'M', 'email':'email@email.com', 'latitude': '-34.58', 'longitude': '-58.60', 'photo_profile':'AAA'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Successful signup")

	#Failed signup	username already in use
	def test_2(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 4)
		self.assertEqual(data["errors"][0]["message"], "Username already in use")	
		
	#Failed signup long username	
	def test_3(self):
		payload= {'username': self._username_long, 'password': 'pass', 'name': 'name', 'age': 20, 'gender':'M', 'email':'email@email.com', 'latitude': '-34.58', 'longitude': '-58.60', 'photo_profile':'AAA'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 500)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 6)
		self.assertEqual(data["errors"][0]["message"], "Server error")

	#Failed signup pass
	def test_4(self):
		payload = {'username': self._username}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 2)
		self.assertEqual(data["errors"][0]["message"], "Empty password")

	#Failed signup username
	def test_5(self):
		payload = {'password': 'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 2)
		self.assertEqual(data["errors"][0]["message"], "Empty username")

	#Failed signup no user no pass
	def test_6(self):
		payload = {}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 2)
		self.assertEqual(data["errors"][0]["message"], "Empty username")
		self.assertEqual(data["errors"][1]["code"], 2)
		self.assertEqual(data["errors"][1]["message"], "Empty password")

	#Failed signup bad json
	def test_7(self):
		payload = ''
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 3)
		self.assertEqual(data["errors"][0]["message"], "Bad Json")
		
	#Successful login
	def test_8(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)

	#Failed login bad credentials
	def test_9(self):
		payload = {'username': 'username','password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Failed login bad password
	def test_10(self):
		payload = {'username': self._username, 'password':'noValidPassword'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Failed login bad json
	def test_11(self):
		payload = ''
		r = requests.post(self.__api_base_url + self._url_usuario + "login", payload)
		self.assertEqual(r.status_code, 400)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 3)
		self.assertEqual(data["errors"][0]["message"], "Bad Json")

	#Successful interests
	def test_12(self):
		r = requests.get(self.__api_base_url + self._url_usuario + "interests")
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertTrue(data["data"]["interests"])

	#Unauthorized like
	def test_13(self):
		payload = {'username': self._username}
		r = requests.put(self.__api_base_url + self._url_usuario + "like", json=payload)
		self.assertEqual(r.status_code, 401)
		self.assertFalse(r.text)

	#Successful signup other username	
	def test_14(self):
		payload= {'username': self._usernamelike, 'password': 'pass', 'name': 'name', 'age': 20, 'gender':'M', 'email':'email@email.com', 'latitude': '-34.58', 'longitude': '-58.60', 'photo_profile':'AAA'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Successful signup")

	#Failed like bad credentials
	def test_15(self):
		r = requests.put(self.__api_base_url + self._url_usuario +  self._usernamelike + "/like")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Successful like and dislike 
	def test_16(self):
		payload = {'username': self._username, 'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		data = json.loads(r.text)
		token = data["data"]["accessToken"]

		auth = {'Authorization': token}
		r = requests.put(self.__api_base_url + self._url_usuario +  self._usernamelike + "/like", headers=auth)

		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Like successful")

		r = requests.put(self.__api_base_url + self._url_usuario +  self._usernamelike + "/dislike", headers=auth)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Dislike successful")

	#Unauthorized dislike
	def test_17(self):
		payload = {'username': self._username}
		r = requests.put(self.__api_base_url + self._url_usuario + "dislike", json=payload)
		self.assertEqual(r.status_code, 401)
		self.assertFalse(r.text)

	#Failed dislike bad credentials
	def test_18(self):
		r = requests.put(self.__api_base_url + self._url_usuario +  self._usernamelike + "/dislike")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEqual(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

