'''
@Author: Shuai Wang
@Github: https://github.com/wsustcid
@Version: 0.0.0
@Date: 2022-03-10 15:26:19
@LastEditTime: 2022-03-10 15:42:02
'''
import unittest
import person

class PersonTestCase(unittest.TestCase):
    """The Unit Test for Person Class
    """
    def __init__(self, methodName: str = ...) -> None:
        super().__init__(methodName)
        self.person1 = person.Person("Zhang San")
        self.person2 = person.Person("Li Si")
    
    def test_get_name(self):
        self.assertEqual(self.person1._get_name(), "Zhang San")
        self.assertEqual(self.person2._get_name(), "Li Si")

if __name__ == '__main__':
    unittest.main()
