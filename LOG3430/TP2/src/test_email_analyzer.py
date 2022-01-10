import unittest
from unittest.mock import Mock
from unittest.mock import patch

from email_analyzer import EmailAnalyzer


class TestEmailAnalyzer(unittest.TestCase):
    def setUp(self):
        self.subject = "subject"
        self.body = "body"
        self.clean_subject = [
            "subject"
        ]  # données pour mocker "return_value" du "clean_text"
        self.clean_body = ["body"]  # données pour mocker "return_value" du "clean_text"
        self.spam_ham_body_prob_true = (
            0.9,
            0.1,
        )  # données pour mocker "return_value" du "spam_ham_body_prob"
        self.spam_ham_subject_prob_true = (
            0.9,
            0.1,
        )  # données pour mocker "return_value" du "subject_spam_ham_prob"
        self.spam_ham_body_prob_false = (
            0.1,
            0.9,
        )  # données pour mocker "return_value" du "spam_ham_body_prob"
        self.spam_ham_subject_prob_false = (
            0.1,
            0.9,
        )  # données pour mocker "return_value" du "subject_spam_ham_prob"
        self.spam_ham_body_prob_expected = (
            0.03703125,
            0.02546875,
        )  # valeurs de la probabilité attendus
        self.spam_ham_subject_prob_expected = (
            0.00462890625,
            0.00318359375,
        )  # valeurs de la probabilité attendus
        self.vocab = {
            "p_sub_spam": {"subject": self.spam_ham_subject_prob_expected[0]},
            "p_sub_ham": {"subject": self.spam_ham_subject_prob_expected[1]},
            "p_body_spam": {"body": self.spam_ham_body_prob_expected[0]},
            "p_body_ham": {"body": self.spam_ham_body_prob_expected[1]},
        }  # vocabulaire avec les valeurs de la probabilité pour mocker "return_value" du "load_dict"

    def tearDown(self):
        pass

    @patch("email_analyzer.EmailAnalyzer.clean_text")
    @patch("email_analyzer.EmailAnalyzer.spam_ham_body_prob")
    @patch("email_analyzer.EmailAnalyzer.spam_ham_subject_prob")
    def test_is_spam_Returns_True_if_spam_prob_is_higher(
        self,
        mock_spam_ham_subject_prob: Mock,
        mock_spam_ham_body_prob: Mock,
        mock_clean_text: Mock,
    ):
        """
        Il faut mocker les fonctions "spam_ham_body_prob" et "subject_spam_ham_prob".
        La sortie de la fonction doit être True si probabilité spam > probabilité ham
        """
        mock_clean_text.side_effect = [self.clean_subject, self.clean_body]
        mock_spam_ham_body_prob.return_value = self.spam_ham_body_prob_true
        mock_spam_ham_subject_prob.return_value = self.spam_ham_subject_prob_true
        self.assertTrue(
            EmailAnalyzer().is_spam(subject_orig=self.subject, body_orig=self.body)
        )

    @patch("email_analyzer.EmailAnalyzer.clean_text")
    @patch("email_analyzer.EmailAnalyzer.spam_ham_body_prob")
    @patch("email_analyzer.EmailAnalyzer.spam_ham_subject_prob")
    def test_is_spam_Returns_False_if_spam_prob_is_lower(
        self,
        mock_spam_ham_subject_prob: Mock,
        mock_spam_ham_body_prob: Mock,
        mock_clean_text: Mock,
    ):
        """
        Il faut mocker les fonctions "spam_ham_body_prob" et "subject_spam_ham_prob".
        La sortie de la fonction doit être False si probabilité spam  probabilité ham
        """
        mock_clean_text.side_effect = [self.clean_subject, self.clean_body]
        mock_spam_ham_body_prob.return_value = self.spam_ham_body_prob_false
        mock_spam_ham_subject_prob.return_value = self.spam_ham_subject_prob_false
        self.assertFalse(
            EmailAnalyzer().is_spam(subject_orig=self.subject, body_orig=self.body)
        )

    @patch("email_analyzer.EmailAnalyzer.load_dict")
    def test_spam_ham_body_prob_Returns_expected_probability(
        self, mock_load_dict: Mock
    ):
        """
        Il faut mocker la fonction "load_dict"
        Il faut vérifier que probabilité est calculée correctement donné le "body" à l'entrée
        """
        mock_load_dict.return_value = self.vocab
        self.assertEqual(
            EmailAnalyzer().spam_ham_body_prob(self.body),
            self.spam_ham_body_prob_expected,
        )

    @patch("email_analyzer.EmailAnalyzer.load_dict")
    def test_subject_spam_ham_prob_Returns_expected_probability(
        self, mock_load_dict: Mock
    ):
        """
        Il faut mocker la fonction "load_dict"
        il faut vérifier que probabilité est calculée correctement donné le "sujet" a l'entrée
        """
        mock_load_dict.return_value = self.vocab
        self.assertEqual(
            EmailAnalyzer().spam_ham_subject_prob(self.subject),
            self.spam_ham_subject_prob_expected,
        )

    @patch("email_analyzer.EmailAnalyzer.load_dict")
    def test_subject_spam_ham_prob_with_word_not_in_vocab(self, mock_load_dict: Mock):
        """
        Il faut mocker la fonction "load_dict"
        il faut vérifier que probabilité est calculée correctement donné le "body" a l'entrée
        """
        mock_load_dict.return_value = self.vocab
        self.assertEqual(EmailAnalyzer().spam_ham_body_prob(""), (0.5925, 0.4075))

    @patch("email_analyzer.EmailAnalyzer.load_dict")
    def test_spam_ham_body_prob_with_word_not_in_vocab(self, mock_load_dict: Mock):
        """
        Il faut mocker la fonction "load_dict"
        il faut vérifier que probabilité est calculée correctement donné le "sujet" a l'entrée
        """
        mock_load_dict.return_value = self.vocab
        self.assertEqual(EmailAnalyzer().spam_ham_subject_prob(""), (0.5925, 0.4075))
