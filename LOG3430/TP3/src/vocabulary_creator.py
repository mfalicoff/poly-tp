import json

from text_cleaner import TextCleaning


class VocabularyCreator:
    """Class for creating vocabulary of spam and non-spam messages"""

    def __init__(self, param):
        self.train_set = "train_set.json"
        self.cleaning = TextCleaning()
        self.vocabulary = "vocabulary.json"
        self.voc_data = {}
        self.param = param

    def compute_proba(self, data, total):
        """
        Description: calcul la probabilité de chaque mot du dictionnaire basé sur
        sa fréquence d'occurence
        Sortie: le dictionnaire des probabilité pour chaque mot
        """
        proba_dict = {}
        for wd in data:
            proba_dict[wd] = data[wd] / total

        return proba_dict

    @staticmethod
    def _filter_min_occurrence(occ: dict, min_occurrence: int) -> dict:
        return dict(filter(lambda kv: kv[1] >= min_occurrence, occ.items()))

    def create_vocab(self, min_occurrence: int = 1):
        """
        Description: fonction pour creer le vocabulaire des mots presents
        dans les e-mails spam et ham et le sauvegarder dans le fichier
        vocabulary.json selon le format specifie dans la description de lab
        Sortie: bool, 'True' pour succes, 'False' dans le cas de failure.
        """
        print("Creating vocabulary")

        dataset = self.load_dict()

        occ_spam_sub = {}
        occ_spam_bod = {}
        occ_ham_sub = {}
        occ_ham_bod = {}

        email_count = len(dataset["dataset"])
        i = 0

        # Analyze each email
        for email in dataset["dataset"]:
            i += 1
            print("\rEmail " + str(i) + "/" + str(email_count), end="")

            # Get data
            data = email["mail"]
            subject = data["Subject"]
            body = data["Body"]
            is_spam = False

            # Update the number of spams / hams
            if data["Spam"] == "true":
                is_spam = True

            # Analyze the subject
            subject = self.cleaning.clean_text(subject, self.param)
            if is_spam:
                for wd in subject:
                    # Add the word to the dictionary or update its occurence count
                    if wd not in occ_spam_sub:
                        occ_spam_sub[wd] = 1
                    else:
                        occ_spam_sub[wd] += 1
            else:
                for wd in subject:
                    # Add the word to the dictionary or update its occurence count
                    if wd not in occ_ham_sub:
                        occ_ham_sub[wd] = 1
                    else:
                        occ_ham_sub[wd] += 1

            # Analyze the body
            body = self.cleaning.clean_text(body, self.param)
            if is_spam:
                for wd in body:
                    # Add the word to the dictionary or update its occurence count
                    if wd not in occ_spam_bod:
                        occ_spam_bod[wd] = 1
                    else:
                        occ_spam_bod[wd] += 1
            else:
                for wd in body:
                    # Add the word to the dictionary or update its occurence count
                    if wd not in occ_ham_bod:
                        occ_ham_bod[wd] = 1
                    else:
                        occ_ham_bod[wd] += 1

        # Create the data dictionary
        occ_spam_sub = self._filter_min_occurrence(occ_spam_sub, min_occurrence)
        occ_ham_sub = self._filter_min_occurrence(occ_ham_sub, min_occurrence)
        occ_spam_bod = self._filter_min_occurrence(occ_spam_bod, min_occurrence)
        occ_ham_bod = self._filter_min_occurrence(occ_ham_bod, min_occurrence)

        p_sub_spam = self.compute_proba(occ_spam_sub, sum(occ_spam_sub.values()))
        p_sub_ham = self.compute_proba(occ_ham_sub, sum(occ_ham_sub.values()))
        p_body_spam = self.compute_proba(occ_spam_bod, sum(occ_spam_bod.values()))
        p_body_ham = self.compute_proba(occ_ham_bod, sum(occ_ham_bod.values()))

        self.voc_data = {
                "p_sub_spam":  p_sub_spam,
                "p_sub_ham":   p_sub_ham,
                "p_body_spam": p_body_spam,
                "p_body_ham":  p_body_ham,
        }

        # Save data
        return self.write_data_to_vocab_file(self.voc_data)

    def load_dict(self):
        with open(self.train_set) as json_data:
            data_dict = json.load(json_data)
        return data_dict

    def write_data_to_vocab_file(self, vocab):
        try:
            with open(self.vocabulary, "w") as outfile:
                json.dump(vocab, outfile)
                print("Vocab created")
                return True
        except:
            return False

    def clean_text(self, text):
        return self.cleaning.clean_text(text, self.param)
