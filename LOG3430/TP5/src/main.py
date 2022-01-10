import json

from email_analyzer import EmailAnalyzer
from renege import RENEGE
from vocabulary_creator import VocabularyCreator


def evaluate(test_filename="test_set.json"):
    tp = 0
    tn = 0
    fp = 0
    fn = 0
    total = 0
    analyzer = EmailAnalyzer()
    with open(test_filename) as email_file:
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

        if ((analyzer.is_spam(subject, body))) and (spam == "true"):
            tp += 1
        if (not (analyzer.is_spam(subject, body))) and (spam == "false"):
            tn += 1
        if ((analyzer.is_spam(subject, body))) and (spam == "false"):
            fp += 1
        if (not (analyzer.is_spam(subject, body))) and (spam == "true"):
            fn += 1
        total += 1

    accuracy = (tp + tn) / (tp + tn + fp + fn)
    precision = tp / (tp + fp)
    recall = tp / (tp + fn)

    return {
        "accuracy": accuracy,
        "precision": precision,
        "recall": recall
    }


if __name__ == "__main__":
    # 1. Creation de vocabulaire.
    vocab = VocabularyCreator()
    vocab.create_vocab()

    # 2. Classification des emails et initialisation de utilisateurs et groupes.
    renege = RENEGE()
    renege.classify_emails()

    # 3. Evaluation de performance du modele avec la fonction evaluate()
    evaluate()
