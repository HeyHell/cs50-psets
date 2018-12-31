import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from passlib.apps import custom_app_context as pwd_context
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Call function from html file
app.jinja_env.globals.update(usd=usd)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get information about user
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]
    stocks = db.execute(
        "SELECT symbol, SUM(quantity) AS total_quantity FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING total_quantity > 0",
        user_id=user_id)

    cur_prices = {}
    for stock in stocks:
        sym = stock["symbol"]
        cur_prices[sym] = lookup(sym)["price"]

    return render_template("portfolio.html",
            purchases=stocks, quotes=cur_prices, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check user input
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Quote is not found", 404)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid number of shares")
        if shares <= 0:
            return apology("Number of shares must be a positive number")

        # Check if the user has enough cash
        user_id = session["user_id"]
        price = shares * quote["price"]
        cash = db.execute("SELECT cash FROM users WHERE id=:id", id=user_id)[0]["cash"]
        if cash < price:
            return apology("You do not have enough cash")

        # Update cash
        db.execute("UPDATE users SET cash = cash - :price WHERE id = :user_id",
                    price=price, user_id=user_id)
        # Add stock to user's portfolio
        db.execute("INSERT INTO purchases (user_id, symbol, total, quantity, datetime) \
                    VALUES(:user_id, :symbol, :total, :shares, :datetime)",
                        user_id=user_id, symbol=symbol, total=price, shares=shares, datetime=datetime.now())

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    purchases = db.execute("SELECT * FROM purchases WHERE user_id=:user_id ORDER BY datetime",
                            user_id=session["user_id"])
    return render_template("history.html", purchases=purchases)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Quote is not found", 404)
        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirm")

        # Ensure that all field are valid
        if not username:
            return apology("must provide username")
        elif not password:
            return apology("must provide password")
        elif not confirm:
            return apology("must confirm password")
        elif password != confirm:
            return apology("password and confirmation does match")

        # Encrypt password
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        # Add user to database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username=username, hash=hash)
        if not result:
            return apology("user already exists")
        session["user_id"] = username

        flash(f"Welcome, {username}!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    stocks = db.execute(
        "SELECT symbol, SUM(quantity) AS total_quantity FROM purchases \
        WHERE user_id = :user_id GROUP BY symbol HAVING total_quantity > 0",
        user_id=session["user_id"])

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check user input
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid number of shares")

        # Check if user has enough stocks
        user_id = session["user_id"]
        quantity = db.execute("SELECT SUM(quantity) AS total_quantity FROM purchases \
                                WHERE user_id = :user_id AND symbol=:symbol",
                                user_id=user_id, symbol=symbol)[0]["total_quantity"]
        if quantity < shares:
            return apology("you don't have enough stocks")

        # Update cash
        price = shares * quote["price"]
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id",
                    price=price, user_id=user_id)

        # Remove stocks (add entry with negative number of shares)
        db.execute("INSERT INTO purchases (user_id, symbol, total, quantity, datetime) \
                    VALUES(:user_id, :symbol, :total, :shares, :datetime)",
                        user_id=user_id, symbol=symbol, total=price, shares=-shares, datetime=datetime.now())

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
