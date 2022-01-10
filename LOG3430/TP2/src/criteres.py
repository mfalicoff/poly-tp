import itertools
from dataclasses import dataclass
from datetime import datetime
from datetime import timedelta
from typing import Iterable
from typing import List
from typing import Optional
from typing import Set

from crud import CRUD


@dataclass
class EmailVars:
    s: Optional[bool] = None
    p: Optional[bool] = None
    h: Optional[bool] = None
    t1: Optional[bool] = None
    t2: Optional[bool] = None
    t3: Optional[bool] = None

    def __hash__(self):
        return hash((
                self.s,
                self.p,
                self.h,
                self.t1,
                self.t2,
                self.t3,
        ))


class Criteres:
    def __init__(self):
        self.crud_ = CRUD()

    def _parse_email(self, email) -> EmailVars:
        sent_from_id = self.crud_.get_user_id(email["From"])
        date_of_first_message = self.crud_.get_user_data(
                sent_from_id, "Date_of_first_seen_message"
        )
        trust_level = self.crud_.get_user_data(sent_from_id, "Trust")

        user_groups = self.crud_.get_user_data(sent_from_id, "Groups")
        group_counter = 1
        total = 0

        for group in user_groups:
            group_id = self.crud_.get_group_id(group)
            total = total + self.crud_.get_groups_data(group_id, "Trust")
            group_counter += 1
        group_trust = total / group_counter

        p = email["Spam"]  # is spam
        h = (
                date_of_first_message + timedelta(days=30) < datetime.now()
        )  # delta entre maintenant et premier message
        t1 = trust_level < 60
        t2 = group_trust < 70
        t3 = trust_level > 75

        return EmailVars(p=p, h=h, t1=t1, t2=t2, t3=t3)

    @staticmethod
    def _logic_func_1(t: EmailVars) -> bool:
        return t.p and (t.h and t.t1 or t.t2) or t.h and t.t2 and not t.t3

    @staticmethod
    def _logic_func_2(t: EmailVars) -> bool:
        return t.p or not t.t3 and t.t2

    def _all_test_cases_logic_func_1(self) -> List[EmailVars]:
        all_tests: List[EmailVars] = []
        for p, h, t1, t2, t3 in itertools.product([True, False], repeat=5):
            t = EmailVars(p=p, h=h, t1=t1, t2=t2, t3=t3)
            t.s = self._logic_func_1(t)
            all_tests.append(t)
        return all_tests

    @staticmethod
    def _restricted_test_cases(test_cases: Iterable[EmailVars], clauses: Set[str]):
        """Test case pairs with the same minor clauses but different major clauses"""
        for major_clause in clauses:
            minor_clauses = clauses.difference({major_clause, })
            for case_a, case_b in itertools.combinations(test_cases, 2):
                minor_clauses_same = all(getattr(case_a, c) == getattr(case_b, c) for c in minor_clauses)
                major_clause_different = getattr(case_a, major_clause) != getattr(case_b, major_clause)
                if minor_clauses_same and major_clause_different:
                    yield major_clause, case_a, case_b

    @staticmethod
    def _general_test_cases(test_cases: Iterable[EmailVars], clauses: Set[str]):
        """Test case pairs with different major clauses"""
        for major_clause in clauses:
            for case_a, case_b in itertools.combinations(test_cases, 2):
                if getattr(case_a, major_clause) != getattr(case_b, major_clause):
                    yield major_clause, case_a, case_b

    @staticmethod
    def _test_cases(test_cases: Iterable[EmailVars], clauses: Set[str]):
        """Test case pairs"""
        for major_clause in clauses:
            for case_a, case_b in itertools.combinations(test_cases, 2):
                if case_a != case_b:
                    yield major_clause, case_a, case_b

    def test_racc(self) -> Iterable[EmailVars]:
        all_tests = self._all_test_cases_logic_func_1()
        test_table = set()
        clauses = {'p', 'h', 't1', 't2', 't3'}
        cases_needed = set(itertools.product(clauses, [True, False]))
        for major_clause, case_a, case_b in self._restricted_test_cases(test_cases=all_tests,
                                                                        clauses=clauses):
            if getattr(case_a, 's') != getattr(case_b, 's') and (
                    (major_clause, True) in cases_needed or (major_clause, False) in cases_needed):
                test_table.add(case_a)
                test_table.add(case_b)
                cases_needed.remove((major_clause, True))
                cases_needed.remove((major_clause, False))
        return test_table

    def test_gacc(self) -> Iterable[EmailVars]:
        all_tests = self._all_test_cases_logic_func_1()
        test_table = set()
        clauses = {'p', 'h', 't1', 't2', 't3'}
        cases_needed = set(itertools.product(clauses, [True, False]))
        for major_clause, case_a, case_b in self._general_test_cases(test_cases=all_tests,
                                                                     clauses=clauses):
            determines_s = getattr(case_a, 's') != getattr(case_b, 's')
            if determines_s and (
                    (major_clause, True) in cases_needed or (major_clause, False) in cases_needed):
                test_table.add(case_a)
                test_table.add(case_b)
                cases_needed.remove((major_clause, True))
                cases_needed.remove((major_clause, False))
        return test_table

    def test_acc(self) -> Iterable[EmailVars]:
        all_tests = self._all_test_cases_logic_func_1()
        test_table = set()
        clauses = {'p', 'h', 't1', 't2', 't3'}
        cases_needed = set(itertools.product(clauses, [True, False]))
        for major_clause, case_a, case_b in self._test_cases(test_cases=all_tests,
                                                             clauses=clauses):
            determines_s = getattr(case_a, 's') != getattr(case_b, 's')
            if determines_s and (
                    (major_clause, True) in cases_needed or (major_clause, False) in cases_needed):
                test_table.add(case_a)
                test_table.add(case_b)
                cases_needed.remove((major_clause, True))
                cases_needed.remove((major_clause, False))
        return test_table

    def test_vns(self):
        # on veut retrouver touts les tests possbiles 2^3 = 8 tests
        all_tests: List[EmailVars] = []
        for p, t2, t3 in itertools.product([True, False], repeat=3):
            t = EmailVars(p=p, t2=t2, t3=t3)
            t.s = self._logic_func_2(t)
            all_tests.append(t)

        # implicant 1 = p implicant 2 = not t3 and t2
        puv_i1: List[EmailVars] = list(
                filter(
                        lambda t: t.p and not (not t.t3 and t.t2),
                        all_tests
                )
        )
        puv_i2: List[EmailVars] = list(
                filter(
                        lambda t: not t.p and not (not t.t3 and t.t2),
                        all_tests
                )
        )

        # on cherche maintenant les PPF, pour chaque clause (on nie la clause impliquante)
        ppf_p = []

        ppf_t3: List[EmailVars] = list(
                filter(
                        lambda t: not t.p and not (not t.s and t.t2),
                        all_tests
                )
        )

        ppf_t2: List[EmailVars] = list(
                filter(
                        lambda t: not t.p and not (not t.s and t.t3),
                        all_tests
                )
        )

        # puvi2, et les ppf ont chacun un tests donc on les ajoute puis on traverse puv1 pour voir si
        # on a un autre test a ajouter
        tests = [puv_i2[0], ppf_t3[0], ppf_t2[0]]
        for test in puv_i1:
            if test in tests:
                return tests
        tests.append(puv_i1[0])

        return tests

    def test_ricc(self):
        all_tests = self._all_test_cases_logic_func_1()

        # Pour chaque clause majeure teste a vrai et a faux, il faut les memes clauses mineures pour un predicat donne
        test_table = set()
        clauses = {'p', 'h', 't1', 't2', 't3'}
        cases_needed = set(itertools.product(clauses, [True, False]))
        for major_clause, case_a, case_b in self._restricted_test_cases(test_cases=all_tests,
                                                                        clauses=clauses):
            determines_s = getattr(case_a, 's') != getattr(case_b, 's')
            if not determines_s and (major_clause, case_a.s) in cases_needed:
                test_table.add(case_a)
                test_table.add(case_b)
                cases_needed.remove((major_clause, case_a.s))
        return test_table


def print_output_table(table: Iterable[EmailVars], columns: Iterable[str]):
    output = "\t".join(columns) + '\n'
    for t in table:
        output += "\t".join([str(int(getattr(t, att))) for att in columns])
        output += "\n"
    print(output)


def main() -> None:
    print("Tests ACC")
    table_racc = Criteres().test_acc()
    print_output_table(table=table_racc, columns=["p", "h", "t1", "t2", "t3", "s"])

    print("Tests GACC")
    table_racc = Criteres().test_gacc()
    print_output_table(table=table_racc, columns=["p", "h", "t1", "t2", "t3", "s"])

    print("Tests RACC")
    table_racc = Criteres().test_racc()
    print_output_table(table=table_racc, columns=["p", "h", "t1", "t2", "t3", "s"])

    print("Tests RICC")
    table_ricc = Criteres().test_ricc()
    print_output_table(table=table_ricc, columns=["p", "h", "t1", "t2", "t3", "s"])

    print("Tests VNS")
    table_vns = Criteres().test_vns()
    print_output_table(table=table_vns, columns=["p", "t2", "t3", "s"])


if __name__ == '__main__':
    main()
