import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        self.positives = []
        self.negatives = []
        """Initialize Analyzer."""
        fileInput1 = open(positives, "r")
        for line in fileInput1:
            if (line[0] != ";"):
                self.positives.append(line.strip( ' ' ))
                self.positives.append(line.strip( '\n' ))
        fileInput2 = open(negatives, "r")
        for line in fileInput2:
            if (line[0] != ";"):
                self.negatives.append(line.strip( ' ' ))
                self.negatives.append(line.strip( '\n' ))
        fileInput1.close()
        fileInput2.close()
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0;
        """from nltk.tokenize import TweetTokenizer
        tokens = TweetTokenizer()
        tokens.tokenize(text)"""
        words = text.split()
        for i in range(0, len(text.split())):
            for  j in range(0, len(self.positives)):
                if (words[i] == self.positives[j]):
                    score += 1
            for k in range(0, len(self.negatives)):
                if(words[i] == self.negatives[k]):
                    score -= 1
        return score
