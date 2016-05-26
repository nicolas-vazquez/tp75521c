import requests
import unittest
import json
import uuid
import ConfigParser

class AccountTest(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(AccountTest, self).__init__(*args, **kwargs)
		self.__api_base_url = "http://localhost:8083/"
		self._url_usuario = "/api/accounts/"

	@classmethod
	def setUpClass(cls):
		cls._username = uuid.uuid4().hex
	

	def test_1(self):
		payload = {'username': "'"+ self._username +"'",'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "signup", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertEqual(data["data"]["message"], "Successful signup")


	def test_2(self):
		payload = {'username': "'"+ self._username +"'",'password':'pass'}
		r = requests.post(self.__api_base_url + self._url_usuario + "login", json=payload)
		self.assertEqual(r.status_code, 200)
		data = json.loads(r.text)
		self.assertTrue(data["data"]["accessToken"])