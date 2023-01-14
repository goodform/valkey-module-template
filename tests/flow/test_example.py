import os
import time
from packaging import version

from RLTest import Env, Defaults, StandardEnv
from includes import *


def test_helloworld():
    sample_len = 1024

    Env().skipOnCluster()
    skip_on_rlec()
    with Env().getConnection() as r:
        res = r.execute_command('example.parse', '1.123')
        assert res == "1.123".encode('ascii')