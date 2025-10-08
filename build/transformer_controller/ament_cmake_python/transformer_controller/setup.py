from setuptools import find_packages
from setuptools import setup

setup(
    name='transformer_controller',
    version='0.0.1',
    packages=find_packages(
        include=('transformer_controller', 'transformer_controller.*')),
)
