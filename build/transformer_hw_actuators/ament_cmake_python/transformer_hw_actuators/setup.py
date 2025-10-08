from setuptools import find_packages
from setuptools import setup

setup(
    name='transformer_hw_actuators',
    version='0.1.0',
    packages=find_packages(
        include=('transformer_hw_actuators', 'transformer_hw_actuators.*')),
)
