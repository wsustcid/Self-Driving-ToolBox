'''
@Author: Shuai Wang
@Github: https://github.com/wsustcid
@Version: 0.0.0
@Date: 2022-03-10 15:23:59
@LastEditTime: 2022-03-10 15:25:25
'''

class Person(object):
    """ The Person Class
    """
    def __init__(self, name) -> None:
        self.name = name 
    def _get_name(self):
        return self.name