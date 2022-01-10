#!/bin/bash
python -m pip install -r requirements.txt
python -m nltk.downloader stopwords

python -m coverage run -m --source=. --omit=exemple.py,main.py,test_*.py,renege.py,text_cleaner.py,venv/* --branch unittest test_crud.py test_email_analyzer.py test_vocabulary_creator.py
python -m coverage report | tee coverage_report.txt
