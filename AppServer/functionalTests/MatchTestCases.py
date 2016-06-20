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
		cls._url_usuario = "/api/accounts/"
		cls._url_matches = "/api/matches/"
		cls._username_long = uuid.uuid4().hex
		cls._username = cls._username_long[0:10]
		payload = {'username': "'"+ cls._username +"'",'password':'pass'}
		r = requests.post(cls.__api_base_url + cls._url_usuario + "signup", json=payload)
		r = requests.post(cls.__api_base_url + cls._url_usuario + "login", json=payload)
		data = json.loads(r.text)
		cls._token = data["data"]["accessToken"]
		
		
	#Bad credentials matches list	
	def test_1(self):
		r = requests.get(self.__api_base_url + self._url_matches)
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials candidates list	
	def test_2(self):
		r = requests.get(self.__api_base_url + self._url_matches + "candidates")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials messages from user	
	def test_3(self):
		user_id = "27"
		r = requests.get(self.__api_base_url + self._url_matches +  user_id + "/messages")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Bad credentials message to user	
	def test_4(self):
		user_id = "27"
		r = requests.put(self.__api_base_url + self._url_matches +  user_id + "/message")
		self.assertEqual(r.status_code, 401)
		data = json.loads(r.text)
		self.assertEquals(data["errors"][0]["code"], 5)
		self.assertEqual(data["errors"][0]["message"], "Bad credentials")

	#Successful matches list 	
	def test_5(self):
		payload = {'Authorization': self._token}
		r = requests.get(self.__api_base_url + self._url_matches, headers=payload)
		self.assertEqual(r.status_code, 200)

	#Successful candidates list	 
	def test_6(self):
		payload = {'Authorization': self._token}
		r = requests.get(self.__api_base_url + self._url_matches + "candidates", headers=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertTrue(data)

	#Successful messages from user	 
	def test_7(self):
		payload = {'Authorization': self._token}
		user_id = "27"
		r = requests.get(self.__api_base_url + self._url_matches +  user_id + "/messages", headers=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertTrue(data["data"]["messages"])

	#Successful message to user	 
	def test_8(self):
		payload = {'Authorization': self._token }
		user_id = "27"
		r = requests.put(self.__api_base_url + self._url_matches +  user_id + "/message", headers=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Successful updated chat")
