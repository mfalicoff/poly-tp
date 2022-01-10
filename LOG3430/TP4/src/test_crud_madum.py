import itertools
import unittest
from crud import CRUD
from dataclasses import asdict
from dataclasses import dataclass
from dataclasses import field
from datetime import datetime
from datetime import timezone
from typing import Callable
from typing import Dict
from typing import List
from typing import Tuple
from typing import Union

DEFAULT_DATE = "2021-12-12"


def convert_to_unix(date):
    dt = datetime.strptime(date, "%Y-%m-%d")
    date = dt.replace(tzinfo=timezone.utc).timestamp()
    return date


@dataclass
class User:
    name: Union[str, bool] = 'user@user.com'
    Date_of_first_seen_message: Union[float, bool] = convert_to_unix(DEFAULT_DATE)
    Date_of_last_seen_message: Union[float, bool] = convert_to_unix(DEFAULT_DATE)
    Trust: Union[int, bool] = 50
    SpamN: Union[int, bool] = 0
    HamN: Union[int, bool] = 0
    Groups: Union[List[str], bool] = field(default_factory=lambda: list(['default']))


@dataclass
class TestResult:
    user_id_for_data: int
    user_id_from_username: int
    user: User
    new_user_id: int


class CrudMadumTest(unittest.TestCase):
    def setUp(self) -> None:
        self.users_data = {
                "0": {
                        "name":                       "alex@gmail.com",
                        "Trust":                      100,
                        "SpamN":                      0,
                        "HamN":                       0,
                        "Date_of_first_seen_message": 1596844800.0,
                        "Date_of_last_seen_message":  1596844800.0,
                        "Groups":                     ["default", "group1"],
                }
        }
        self.groups_data = {}
        self.user = {
                "name":                       "test@example.com",
                "Trust":                      100,
                "SpamN":                      0,
                "HamN":                       0,
                "Date_of_first_seen_message": 1596844800.0,
                "Date_of_last_seen_message":  1596844800.0,
                "Groups":                     ["default"],
        }
        self.crud = CRUD(users_data=self.users_data, groups_data=self.groups_data)
        self._callables = list(
                zip(range(1, 5), [
                        ('add_new_user', [User.name, DEFAULT_DATE]),
                        ('update_users', [1, "HamN", 100]),
                        ('remove_user', ["0"]),
                        ('remove_user_group', [1, "group1"]),
                ]))
        self._callables_3_1_2_4 = [
                ('remove_user', ["0"]),
                ('add_new_user', [User.name, DEFAULT_DATE]),
                ('update_users', [0, "HamN", 100]),
                ('remove_user_group', [0, "group1"]),
        ]
        self._user_a = User()
        self._user_b = User(HamN=100)
        self._user_c = User(name=False, Date_of_first_seen_message=False, Date_of_last_seen_message=False, Trust=False,
                            Groups=False)
        self._results: Dict[str, TestResult] = {
                "1 2 3 4": TestResult(user_id_for_data=1, user_id_from_username=1, user=self._user_b, new_user_id=0),
                "2 1 3 4": TestResult(user_id_for_data=1, user_id_from_username=1, user=self._user_a, new_user_id=0),
                "3 1 2 4": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_b, new_user_id=1),
                "1 3 2 4": TestResult(user_id_for_data=1, user_id_from_username=1, user=self._user_b, new_user_id=0),
                "2 3 1 4": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "3 2 1 4": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "3 2 4 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "2 3 4 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "4 3 2 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "3 4 2 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "2 4 3 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "4 2 3 1": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "4 1 3 2": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "1 4 3 2": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "3 4 1 2": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "4 3 1 2": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "1 3 4 2": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "3 1 4 2": TestResult(user_id_for_data=0, user_id_from_username=0, user=self._user_a, new_user_id=1),
                "2 1 4 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "1 2 4 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "4 2 1 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "2 4 1 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "1 4 2 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
                "4 1 2 3": TestResult(user_id_for_data=0, user_id_from_username=1, user=self._user_c, new_user_id=0),
        }

    # constructor test
    def test_constructor(self):
        self.crud = CRUD(users_data=self.users_data, groups_data=self.groups_data)
        self.assertEqual(self.crud.users_data, self.users_data)

    # getters
    def test_getters(self):
        user_id = 0
        user = self.users_data[str(user_id)]
        crud_user = dict((k, self.crud.get_user_data(user_id, k)) for k in user.keys())
        self.assertDictEqual(user, crud_user)

    def test_permutations(self):
        for p in itertools.permutations(self._callables):
            p = list(p)
            order = " ".join(str(i) for i, c in p)
            with self.subTest(msg=f"test order {order}"):
                self.setUp()
                if order == "3 1 2 4":
                    for c_ in self._callables_3_1_2_4:
                        method, args = c_
                        getattr(self.crud, method)(*args)
                else:
                    for i, c in p:
                        method, args = c
                        getattr(self.crud, method)(*args)
                expected = self._results[order]
                user_dict = asdict(expected.user)
                crud_user = dict(
                        (k, self.crud.get_user_data(expected.user_id_for_data, k)) for k in user_dict.keys())
                self.assertDictEqual(user_dict, crud_user)
                self.assertEqual(str(expected.user_id_from_username), self.crud.get_user_id(User.name))
                self.assertEqual(str(expected.new_user_id), self.crud.get_new_user_id())


if __name__ == '__main__':
    unittest.main()
