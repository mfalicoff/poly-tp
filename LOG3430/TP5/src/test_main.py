import json
import random
from unittest import TestCase

from main import evaluate
from renege import RENEGE
from vocabulary_creator import VocabularyCreator

WORDS = [
    "counselled",
    "overneat",
    "enzymatically",
    "inaptness",
    "nonsport",
    "cane-trash",
    "stealingly",
    "pandus",
    "guilted",
    "electrolytes",
    "anethum",
    "sorts",
    "guiltie",
    "wordhood",
    "mountainous",
    "ingredients",
    "nonfliers",
    "misleadingly",
    "mahi-mahi",
    "unsent",
    "puckishness",
    "toiletries",
    "Nordloh",
    "recreancy",
    "chargeful",
    "encrypts",
    "shantey",
    "forment",
    "vesuvin",
    "stannite",
    "anticollision",
    "destoor",
    "pentamer",
    "overfill",
    "unbolts",
    "preveniences",
    "reasty",
    "galega",
    "effemination",
    "retroelement",
    "bunglesome",
    "wooziest",
    "hemophilia",
    "brewmaster",
    "sesbania",
    "scratchie",
    "wholewheat",
    "phonies",
    "baudrey",
    "hydrarthrosis",
    "subsannation",
    "phonotactics",
    "metre",
    "hijabs",
    "outpoints",
    "PICCs",
    "synchroniser",
    "pushpit",
    "achatours",
    "ristorante",
    "liquorice",
    "linkify",
    "hutches",
    "ground-robin",
    "serger",
    "nephelium",
    "bioscopic",
    "compersion",
    "Gran Chaco",
    "teocalli",
    "theft",
    "molle",
    "dysteleologist",
    "phenakistoscope",
    "sidewinders",
    "water-bar",
    "watercolor",
    "hydrograph",
    "outspin",
    "runnier",
    "divorces",
    "columniated",
    "jurant",
    "clothe",
    "Saskatonian",
    "facemask",
    "decodings",
    "resolutionists",
    "kamacite",
    "sageship",
    "megalodon",
    "isobilateral",
    "volcanogenic",
    "jovially",
    "icaridin",
    "addendum",
    "conjugative",
    "programs",
    "bigheaded",
    "fishtailed",
]


class MetamorphicTest(TestCase):
    initial_acc = None
    THRESHOLD = 0.03
    train = "train_set.json"
    test = "test_set.json"

    def __init__(self, method_name: str = ...):
        super().__init__(method_name)

    @classmethod
    def setUpClass(cls) -> None:
        vocab = VocabularyCreator(cls.train)
        vocab.create_vocab()
        renege = RENEGE(cls.train)
        if not renege.classify_emails():
            raise RuntimeError("Error classify emails")
        evaluation = evaluate(cls.test)
        cls.initial_acc = evaluation["accuracy"]
        print("Initial accuracy: {}".format(cls.initial_acc))

    @staticmethod
    def _load_json(filename):
        with open(filename, "r") as json_data:
            data = json.load(json_data)
        return data

    @staticmethod
    def _save_to_json(filename, data) -> bool:
        with open(filename, "w") as json_file:
            json.dump(data, json_file, indent=2)
        return True

    def _return_accuracy_from_test(self) -> float:
        vocab_filename = "vocabulary.json"
        vocab = VocabularyCreator(self.train, vocab_filename)
        vocab.create_vocab()
        renege = RENEGE(self.train)
        if not renege.classify_emails():
            raise RuntimeError("Error classify emails")
        evaluation = evaluate(self.test)
        return evaluation["accuracy"]

    def get_accuracy_delta(self):
        return abs(self.initial_acc - self.new_acc)

    @staticmethod
    def _shuffle_email_words(email):
        for mail in email:
            split_table = mail["mail"]["Body"].split()
            random.shuffle(split_table)
            mail["mail"]["Body"] = ' '.join(split_table)
        return email

    @staticmethod
    def _add_noise(email):
        #TODO
        pass

    def test1(self):
        trainset = self._load_json("train_set.json")["dataset"]
        random.shuffle(trainset)
        self.train = "train700_mails.json"
        self._save_to_json(filename=self.train, data={"dataset": trainset})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
            "Le changement d'ordre des emails modifie l'accuracy de beaucoup.",
        )

    def test2(self):
        test_set = self._load_json("test_set.json")["dataset"]
        random.shuffle(test_set)
        self.test = "test300_mails.json"
        self._save_to_json(self.test, {"dataset": test_set})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
            "Le changement d'ordre des emails dans le testset modifie modifie l'accuracy de beaucoup.",
        )

    def test3(self):
        #Changement d'orde des mots dans train dataset
        test_set = self._load_json("train_set.json")["dataset"]
        shuffled_emails_words = self._shuffle_email_words(test_set)
        self.train = "train700_words.json"
        self._save_to_json(self.train, {"dataset": shuffled_emails_words})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
        )

    def test4(self):
        test_set = self._load_json("test_set.json")["dataset"]
        shuffled_emails_words = self._shuffle_email_words(test_set)
        self.test = "test300_words.json"
        self._save_to_json(self.test, {"dataset": shuffled_emails_words})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
            "Le changement d'ordre des mots dans le 'test dataset' modifie l'accuracy de beaucoup.",
        )

    def test5(self):
        #Ajout des memes email dans train dataset
        self.train = "train700x2.json"
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
        )

    def test6(self):
        #Ajout des memes email dans test dataset
        self.test = "test300x2.json"
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
        )

    def test7(self):
        #Bruit dans train dataset
        test_set = self._load_json("train_set.json")["dataset"]
        noised_emails_words = self._add_noise(test_set)
        self.train = "train700_noise.json"
        self._save_to_json(self.train, {"dataset": noised_emails_words})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
        )

    def test8(self):
        #Bruit dans test dataset
        test_set = self._load_json("test_set.json")["dataset"]
        noised_emails_words = self._add_noise(test_set)
        self.test = "test300_noise.json"
        self._save_to_json(self.test, {"dataset": noised_emails_words})
        self.new_acc = self._return_accuracy_from_test()
        self.assertLessEqual(
            self.get_accuracy_delta(),
            self.THRESHOLD,
        )


