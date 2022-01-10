import unittest
from unittest.mock import patch

import vocabulary_creator


class TestVocabularyCreator(unittest.TestCase):
    def setUp(self):
        self.mails = {
            "dataset": [
                {
                    "mail": {
                        "Subject": "sspam_1 sspam_2 ss_pam_3 ss_pam_4",
                        "From": "GP@paris.com",
                        "Date": "2000-09-15",
                        "Body": "bspam",
                        "Spam": "true",
                        "File": "enronds//enron4/spam/4536.2005-03-04.GP.spam.txt",
                    }
                },
                {
                    "mail": {
                        "Subject": "sham_1 sham_2 sh_am_3 sh_am_4",
                        "From": "farmer@paris.com",
                        "Date": "2000-09-15",
                        "Body": "bham1 bham_2 bham_3 bham_4",
                        "Spam": "false",
                        "File": "enronds//enron1/ham/2256.2000-09-15.farmer.ham.txt",
                    }
                },
            ]
        }

        self.vocab_clean_subjects = [
            ["sham_1", "sham_2", "sh_am_3", "sh_am_4"],
            ["sspam_1", "sspam_2", "ss_pam_3", "ss_pam_4"],
        ]
        self.vocab_clean_body = [["bham1", "bham_2", "bham_3", "bham_4"], ["bspam"]]

        self.vocab_expected = {
            "p_sub_spam": {"sspam": 0.5, "pam": 0.5},
            "p_sub_ham": {"sham": 1.0},
            "p_body_spam": {"bspam": 1.0},
            "p_body_ham": {"bham": 1.0},
        }

        self.order = 1

    def tearDown(self):
        pass

    @patch("vocabulary_creator.VocabularyCreator.load_dict")
    @patch("vocabulary_creator.VocabularyCreator.clean_text")
    @patch("vocabulary_creator.VocabularyCreator.write_data_to_vocab_file")
    def test_create_vocab_spam_Returns_vocabulary_with_correct_values(
        self, mock_write_data_to_vocab_file, mock_clean_text, mock_load_dict
    ):
        """Description: Tester qu'un vocabulaire avec les probabilités calculées
        correctement va être retourné. Il faut mocker les fonctions "load dict"
         (utiliser self.mails comme un return value simulé),"clean text"
         (cette fonction va être appelé quelques fois, pour chaque appel on
         va simuler la return_value different, pour cela il faut utiliser
         side_effect (vois l'exemple dans l'énonce)) et
         "write_data_to_vocab_file" qui va simuler "return True" au lieu
         d'écrire au fichier "vocabulary.json".
         if faut utiliser self.assertEqual(appele_a_create_vocab(), self.vocab_expected)
        """

        clean_text = [
            self.vocab_clean_body[0],
            self.vocab_clean_subjects[0],
            self.vocab_clean_body[1],
            self.vocab_clean_subjects[1],
        ]

        def clean_text_mock():
            return clean_text.pop()

        vocab_ = vocabulary_creator.VocabularyCreator()
        mock_load_dict.return_value = self.mails
        mock_clean_text.side_effect = clean_text_mock
        mock_write_data_to_vocab_file.return_value = True

        self.assertEqual(vocab_.create_vocab(), True)
        self.assertEqual(vocab_.voc_data, self.vocab_expected)
