#!/bin/bash
python -m pip install -r requirements.txt
python -m nltk.downloader stopwords

python -m unittest test_main.MetamorphicTest

