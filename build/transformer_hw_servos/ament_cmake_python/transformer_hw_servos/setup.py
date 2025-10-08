from setuptools import find_packages
from setuptools import setup

setup(
    name='transformer_hw_servos',
    version='0.1.0',
    packages=find_packages(
        include=('transformer_hw_servos', 'transformer_hw_servos.*')),
)
