import copy
import datetime
import unittest
from unittest.mock import patch

from crud import CRUD


class TestCRUD(unittest.TestCase):
    def setUp(self):
        # c'est un exemple de données "mock" à utiliser comme "return value" de read_users_file
        self.users_data = {
            "1": {
                "name": "alex@gmail.com",
                "Trust": 100,
                "SpamN": 0,
                "HamN": 20,
                "Date_of_first_seen_message": 1596844800.0,
                "Date_of_last_seen_message": 1596844800.0,
                "Groups": ["default"],
            },
            "2": {
                "name": "mark@mail.com",
                "Trust": 65.45454,
                "SpamN": 171,
                "HamN": 324,
                "Date_of_first_seen_message": 1596844800.0,
                "Date_of_last_seen_message": 1596844800.0,
                "Groups": ["default"],
            },
        }
        # c'est un exemple de données "mock" à utiliser comme "return value" de read_groups_file
        self.groups_data = {
            "1": {
                "name": "default",
                "Trust": 50,
                "List_of_members": ["alex@gmail.com", "mark@mail.com"],
            },
            "2": {
                "name": "friends",
                "Trust": 90,
                "List_of_members": ["alex@gmail.com"],
            },
        }

    def tearDown(self):
        pass

    @patch("crud.CRUD.read_users_file")
    @patch("crud.CRUD.modify_users_file")
    def test_add_new_user_Passes_correct_data_to_modify_users_file(
        self,
        mock_modify_users_file,
        mock_read_users_file,
    ):
        """Description: il faut utiliser les mocks des fonctions "read_users_file",
        "modify_users_file", "modify_groups_file" (ou selon votre realisation) pour tester que
        l'information a ajouter pour l'utilisateur a été formée correctement par la fonction, e.g.
        self.modify_users_file(data) -> "data" doit avoir un format et contenu expectee
        il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        dt = datetime.datetime.strptime("2021-09-25", "%Y-%m-%d")
        date = dt.replace(tzinfo=datetime.timezone.utc).timestamp()
        expected_data["0"] = {
            "name": "test@gmail.com",
            "Trust": 50,
            "SpamN": 0,
            "HamN": 0,
            "Date_of_first_seen_message": date,
            "Date_of_last_seen_message": date,
            "Groups": ["default"],
        }
        crud_.add_new_user("test@gmail.com", "2021-09-25")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.read_users_file")
    @patch("crud.CRUD.read_groups_file")
    @patch("crud.CRUD.modify_groups_file")
    def test_add_new_group_Passes_correct_data_to_modify_groups_file(
        self, mock_modify_groups_file, mock_read_groups_file, mock_read_users_file
    ):
        """Description: il faut utiliser les mocks des fonctions "read_groups_file",
        "modify_groups_file" (ou selon votre realisation) pour tester que
        l'information a ajouter pour le groupe a étée formée correctement par la fonction e.g.
        self.modify_groups_file(data) -> "data" doit avoir un format et contenu attendu
        il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        mock_read_groups_file.return_value = self.groups_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.groups_data)
        expected_data["0"] = {
            "name": "test",
            "Trust": "50",
            "List_of_members": ["alex@gmail.com", "mark@mail.com"],
        }
        crud_.add_new_group("test", "50", ["alex@gmail.com", "mark@mail.com"])
        mock_modify_groups_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.read_users_file")
    def test_get_user_data_Returns_false_for_invalid_id(self, mock_read_users_file):
        """Description: il faut utiliser le mock de fonction "read_users_file",
        (ou selon votre realisation) pour tester que false (ou bien une excepton)
        est returnee par la fonction si ID non-existant est utilisée
        il faut utiliser ".assertEqual()" ou ".assertFalse()"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        self.assertEqual(crud_.get_user_data("123", "SpamN"), False)

    @patch("crud.CRUD.read_users_file")
    def test_get_user_data_Returns_false_for_invalid_field(self, mock_read_users_file):
        """Description: il faut utiliser le mock de fonction "read_groups_file",
        (ou selon votre realisation) pour tester que false (ou bien une excepton)
        est returnee par la fonction si champ non-existant est utilisée
        il faut utiliser ".assertEqual()" ou ".assertFalse()"
        """
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().get_user_data("1", "Something"), False)

    @patch("crud.CRUD.read_users_file")
    def test_get_user_data_Returns_correct_value_if_field_and_id_are_valid(
        self, mock_read_users_file
    ):
        """Description: il faut utiliser le mock de fonction "read_groups_file",
        (ou selon votre realisation) pour tester que une bonne valeur est fournie
        si champ est id valide sont utilisee
        il faut utiliser ".assertEqual()""
        """
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().get_user_data("1", "SpamN"), 0)

    @patch("crud.CRUD.read_groups_file")
    def test_get_groups_data_Returns_false_for_invalid_id(self, mock_read_groups_file):
        """
        Similar test_get_user_data_Returns_false_for_invalid_id
        """
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().get_groups_data("123", "name"), False)

    @patch("crud.CRUD.read_groups_file")
    def test_get_group_data_Returns_false_for_invalid_field(
        self, mock_read_groups_file
    ):
        """
        Similare test_get_user_data_Returns_false_for_invalid_field
        """
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().get_groups_data("1", "something"), False)

    @patch("crud.CRUD.read_groups_file")
    def test_get_group_data_Returns_correct_value_if_field_and_id_are_valid(
        self, mock_read_groups_file
    ):
        """
        Similare test_get_user_data_Returns_correct_value_if_field_and_id_are_valid
        """
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().get_groups_data("1", "name"), "default")

    @patch("crud.CRUD.read_users_file")
    def test_get_user_id_Returns_false_for_invalid_user_name(
        self, mock_read_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().get_user_id("test"), False)

    @patch("crud.CRUD.read_users_file")
    def test_get_user_id_Returns_id_for_valid_user_name(self, mock_read_users_file):
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().get_user_id("alex@gmail.com"), "1")

    @patch("crud.CRUD.read_groups_file")
    def test_get_group_id_Returns_false_for_invalid_group_name(
        self, mock_read_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().get_group_id("test"), False)

    @patch("crud.CRUD.read_groups_file")
    def test_get_group_id_Returns_id_for_valid_group_name(self, mock_read_groups_file):
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().get_group_id("default"), "1")

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    # Modify_user_file mock est inutile pour tester False pour update
    def test_update_users_Returns_false_for_invalid_id(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        """
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().update_users("123", "test", "test"), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Returns_false_for_invalid_field(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        """
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().update_users("1", "test", "test"), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Passes_correct_data_to_modify_users_file(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["name"] = "test@gmail.com"
        crud_.update_users("1", "name", "test@gmail.com")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_update_groups_Returns_false_for_invalid_id(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        """
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_groups("123", "name", "test"), False)
        mock_modify_groups_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_update_groups_Returns_false_for_invalid_field(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        """
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_groups("123", "test", "test"), False)
        mock_modify_groups_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_update_groups_Passes_correct_data_to_modify_groups_file(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_groups_file.return_value = self.groups_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.groups_data)
        expected_data["1"]["name"] = "test"
        crud_.update_groups("1", "name", "test")
        mock_modify_groups_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_remove_user_Returns_false_for_invalid_id(
        self, mock_read_users_file, mock_modify_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().remove_user("123"), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_remove_user_Passes_correct_value_to_modify_users_file(
        self, mock_read_users_file, mock_modify_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        del expected_data["1"]
        crud_.remove_user("1")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_remove_user_group_Returns_false_for_invalid_id(
        self, mock_read_users_file, mock_modify_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().remove_user_group("123", "default"), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_remove_user_group_Returns_false_for_invalid_group(
        self, mock_read_users_file, mock_modify_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        self.assertEqual(CRUD().remove_user_group("1", "test"), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_remove_user_group_Passes_correct_value_to_modify_users_file(
        self, mock_read_users_file, mock_modify_users_file
    ):
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["Groups"] = []
        crud_.remove_user_group("1", "default")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_remove_group_Returns_false_for_invalid_id(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().remove_group("123"), False)
        mock_modify_groups_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_remove_group_Passes_correct_value_to_modify_groups_file(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.groups_data)
        del expected_data["1"]
        crud_.remove_group("1")
        mock_modify_groups_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_remove_group_member_Returns_false_for_invalid_id(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().remove_group_member("123", "alex@gmail.com"), False)
        mock_modify_groups_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_remove_group_member_Returns_false_for_invalid_group_member(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().remove_group_member("1", "test@gmail.com"), False)
        mock_modify_groups_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_remove_group_member_Passes_correct_value_to_modify_groups_file(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        mock_read_groups_file.return_value = self.groups_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.groups_data)
        expected_data["1"]["List_of_members"] = ["mark@mail.com"]
        crud_.remove_group_member("1", "alex@gmail.com")
        mock_modify_groups_file.assert_called_once_with(expected_data)

    ###########################################
    #               CUSTOM TEST               #
    ###########################################

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Passes_correct_data_to_modify_users_file_Date_of_last_seen_message(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["Date_of_last_seen_message"] = 1630022400.0
        crud_.update_users("1", "Date_of_last_seen_message", "2021-08-27")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Passes_correct_data_to_modify_users_file_Date_of_first_seen_message(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["Date_of_first_seen_message"] = 967334400.0
        crud_.update_users("1", "Date_of_first_seen_message", "2000-08-27")
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Passes_correct_data_to_modify_users_Trust(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["Trust"] = 74
        crud_.update_users("1", "Trust", 74)
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_Passes_correct_data_to_modify_users_SpamN_HamN(
        self, mock_read_users_file, mock_modify_users_file
    ):
        """Il faut utiliser les mocks pour 'read_users_file' et 'modify_users_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.users_data)
        expected_data["1"]["SpamN"] = 74
        crud_.update_users("1", "SpamN", 74)
        mock_modify_users_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.read_groups_file")
    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_return_false_on_wrong_Groups(
        self, mock_read_users_file, mock_modify_users_file, mock_read_groups_file
    ):
        mock_read_users_file.return_value = self.users_data
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_users("1", "Groups", ["test"]), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.read_groups_file")
    @patch("crud.CRUD.modify_users_file")
    @patch("crud.CRUD.read_users_file")
    def test_update_users_return_false_on_wrong_field(
        self, mock_read_users_file, mock_modify_users_file, mock_read_groups_file
    ):
        mock_read_users_file.return_value = self.users_data
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_users("1", "test", ""), False)
        mock_modify_users_file.assert_not_called()

    @patch("crud.CRUD.modify_groups_file")
    @patch("crud.CRUD.read_groups_file")
    def test_update_groups_Passes_correct_data_to_modify_groups_file_Trust(
        self, mock_read_groups_file, mock_modify_groups_file
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_groups_file.return_value = self.groups_data
        crud_ = CRUD()
        expected_data = copy.deepcopy(self.groups_data)
        expected_data["1"]["Trust"] = 74
        crud_.update_groups("1", "Trust", 74)
        mock_modify_groups_file.assert_called_once_with(expected_data)

    @patch("crud.CRUD.read_users_file")
    @patch("crud.CRUD.read_groups_file")
    @patch("crud.CRUD.modify_groups_file")
    def test_update_groups_return_false_on_wrong_List_of_members(
        self,
        mock_read_users_file,
        mock_read_groups_file,
        mock_modify_groups_file,
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_groups("1", "List_of_members", ["test"]), False)
        mock_modify_groups_file.assert_called_once()

    @patch("crud.CRUD.read_users_file")
    @patch("crud.CRUD.read_groups_file")
    @patch("crud.CRUD.modify_groups_file")
    def test_update_groups_return_false_on_wrong_field(
        self,
        mock_read_users_file,
        mock_read_groups_file,
        mock_modify_groups_file,
    ):
        """Il faut utiliser les mocks pour 'read_groups_file' et 'modify_groups_file'
        (ou selon votre realisation)
        Il faut utiliser ".assert_called_once_with(expected_data)"
        """
        mock_read_users_file.return_value = self.users_data
        mock_read_groups_file.return_value = self.groups_data
        self.assertEqual(CRUD().update_groups("1", "test", ""), False)
        mock_modify_groups_file.assert_called_once()
