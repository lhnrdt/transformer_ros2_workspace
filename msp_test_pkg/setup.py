from setuptools import setup

package_name = 'msp_test_pkg'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    install_requires=['setuptools', 'pyserial'],
    zip_safe=True,
    maintainer='your_name',
    maintainer_email='your@email.com',
    description='Minimal MSP test over serial',
    entry_points={
        'console_scripts': [
            'msp_test_node = msp_test_pkg.msp_node:main',
        ],
    },
)