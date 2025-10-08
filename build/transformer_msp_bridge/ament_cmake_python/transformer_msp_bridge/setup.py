from setuptools import find_packages
from setuptools import setup

setup(
    name='transformer_msp_bridge',
    version='0.0.1',
    packages=find_packages(
        include=('transformer_msp_bridge', 'transformer_msp_bridge.*')),
)
