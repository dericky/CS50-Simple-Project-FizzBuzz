from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys

from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)
    score = 0
    numberPositive = 0
    numberNegative = 0
    totalTweets = len(tweets)
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    for i in range(0, len(tweets)):
        if(analyzer.analyze(tweets[i]) > 0):
            score += 1
            numberPositive += 1
        elif(analyzer.analyze(tweets[i]) < 0):
            score -= 1
            numberNegative += 1
    # TODO
    positive, negative, neutral = (numberPositive/totalTweets)*100, (numberNegative/totalTweets)*100, 100-((numberPositive/totalTweets)*100+(numberNegative/totalTweets)*100)

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
