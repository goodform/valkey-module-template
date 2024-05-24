import unittest
import os
from vkmtest import ModuleTestCase

class MyTestCase(ModuleTestCase(module_path="")):
            
    def testCmd(self):
        self.assertEqual(self.cmd('example.parse', '2'), '0')

if __name__ == '__main__':
    unittest.main()