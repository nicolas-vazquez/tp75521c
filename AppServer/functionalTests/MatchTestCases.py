import requests
import unittest
import json
import uuid
import ConfigParser

class MatchTest(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(MatchTest, self).__init__(*args, **kwargs)
		self.__api_base_url = "http://localhost:8083/"
		self._url_usuario = "/api/accounts/"
		self._url_matches = "/api/matches/"

	@classmethod
	def setUpClass(cls):
		cls._username_long = uuid.uuid4().hex
		cls._username = cls._username_long[0:10]
		cls._token = ""
		
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

	#TODO add auth token and run successful tests