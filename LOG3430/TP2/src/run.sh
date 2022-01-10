#!/bin/bash
python -m pip install -r requirements.txt
python -m nltk.downloader stopwords

python criteres.py
