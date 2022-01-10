import argparse
import csv
import json
from typing import List
from typing import OrderedDict
from typing import Tuple

import tabulate

from email_analyzer import EmailAnalyzer
from renege import RENEGE
from vocabulary_creator import VocabularyCreator

parser = argparse.ArgumentParser()
parser.add_argument('--csv_filepath', required=False, default='renege-output.csv', help='Path to csv file')


def evaluate(log_, prob_, param_) -> Tuple[float, float, float]:
    tp = 0
    tn = 0
    fp = 0
    fn = 0
    total = 0
    analyzer = EmailAnalyzer()
    with open("test_set.json") as email_file:
        new_emails = json.load(email_file)

    i = 0
    email_count = len(new_emails["dataset"])

    print("Evaluating emails ")
    for e_mail in new_emails["dataset"]:
        i += 1
        print("\rEmail " + str(i) + "/" + str(email_count), end="")

        new_email = e_mail["mail"]
        subject = new_email["Subject"]
        body = new_email["Body"]
        spam = new_email["Spam"]

        if (analyzer.is_spam(subject, body, log_, prob_, param_)) and (spam == "true"):
            tp += 1
        if (not (analyzer.is_spam(subject, body, log_, prob_, param_))) and (spam == "false"):
            tn += 1
        if (analyzer.is_spam(subject, body, log_, prob_, param_)) and (spam == "false"):
            fp += 1
        if (not (analyzer.is_spam(subject, body, log_, prob_, param_))) and (spam == "true"):
            fn += 1
        total += 1

    accuracy = round((tp + tn) / (tp + tn + fp + fn), 2)
    precision = round(tp / (tp + fp), 2)
    recall = round(tp / (tp + fn), 2)
    print("")
    print("\nAccuracy: ", accuracy)
    print("Precision: ", precision)
    print("Recall: ", recall)
    return accuracy, precision, recall


def _read_csv(filepath: str):
    with open(filepath) as f:
        no_comments = filter(lambda row: row[0] != '#', f.readlines())
        r = csv.DictReader(no_comments, delimiter=',')
        return list(r)


def print_results(test_suite: List[OrderedDict], results):
    data = []
    for test, result in zip(test_suite, results):
        data.append(list(test.values()) + list(map(str, result)))
    t = tabulate.tabulate(data, headers=['log', 'prob', 'param', 'voc', 'accuracy', 'precision', 'recall'])
    print(t)


def evaluate_test_suite(test_suite: List[OrderedDict]):
    for test in test_suite:
        log_prob = bool(test['log_prob'])
        prob_merge = bool(test['prob_merge'])
        nettoyage = int(test['nettoyage'])
        voc = int(test['vocab'])

        # 1. Creation de vocabulaire.
        vocab = VocabularyCreator(nettoyage)
        vocab.create_vocab(voc)

        # 2. Classification des emails et initialisation de utilisateurs et groupes.
        renege = RENEGE()

        renege.classify_emails(log_prob, prob_merge, nettoyage)

        # 3. Evaluation de performance du modele avec la fonction evaluate()
        accuracy, precision, recall = evaluate(log_=log_prob, prob_=prob_merge, param_=nettoyage)
        yield accuracy, precision, recall


def main(args=None):
    args = parser.parse_args(args=args)
    test_suite = _read_csv(args.csv_filepath)
    results = list(evaluate_test_suite(test_suite))
    print_results(test_suite, results)


if __name__ == "__main__":
    import sys

    main(sys.argv[1:])
