# BEGIN CODE HERE
from flask import Flask, request, Response, jsonify
from flask_pymongo import PyMongo
from flask_cors import CORS
from pymongo import TEXT, MongoClient
from selenium import webdriver
from selenium.webdriver.common.by import By
# END CODE HERE

app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb://127.0.0.1:27017/pspi"
CORS(app)
mongo = PyMongo(app)
mongo.db.products.create_index([("name", TEXT)])


@app.route("/search", methods=["GET"])
def search():
    # BEGIN CODE HERE


    # Code testing (Insert the sample data into the "products" collection)
    """
    # Create a new MongoClient instance and connect to a running MongoDB server
    client = MongoClient('mongodb://localhost:27017/')

    # Select the database to use
    db = client['pspi']

    # Select the collection to use
    products = db['products']

    # Delete all existing documents in the collection
    products.delete_many({})

    # Insert the sample data into the "products" collection
    result = products.insert_many([
        {
            "id": 1,
            "name": "Paper A4",
            "production_year": 2021,
            "price": 100,
            "color": 54,
            "size": 35
        },
        {
            "id": 2,
            "name": "Paper A3",
            "production_year": 2020,
            "price": 200,
            "color": 65,
            "size": 3
        }
    ])
    """

    # Get the name parameter from the query string
    searchbox = request.args.get('name')

    # Query the database for products with matching name, sorted by price in descending order
    products = mongo.db.products.find({'name': {'$regex': searchbox, '$options': 'i'}}).sort('price', -1)


    # Convert the products cursor to a list of JSON objects
    result = []
    for product in products:
        item = {
            'id': str(product['id']),
            'name': product['name'],
            'production_year': product['production_year'],
            'price': product['price'],
            'color': product['color'],
            'size': product['size']
        }
        result.append(item)

    # Return the result as JSON
    return jsonify(result)


    # END CODE HERE


@app.route("/add-product", methods=["POST"])
def add_product():
    # BEGIN CODE HERE

    # Getting JSON data as a python DICT
    data = request.get_json()   
    
    # Verify data integrity
    def get_type(value):
        if isinstance(value, dict):
            return {key: get_type(value[key]) for key in value}
        else:
            return str(type(value))
        
    expected_schema = {
        "id"                :"",
        "name"              :"",
        "production_year"   :0,
        "price"             :0,
        "color"             :0,
        "size"              :0
    }

    # If the data doesn't match the schema, return an error
    if get_type(data) != get_type(expected_schema):
        return Response("{'error':'Unexpected data syntax'}", status=406, mimetype='application/json')
    
    # Access the database collection
    products = mongo.db.products

    # Check if another product with the same name exists, and update it
    found_and_updated = products.find_one_and_update({"name": data["name"]}, {'$set' : data})

    # If the product doesn't exist, add it to the DB
    if not found_and_updated:
        products.insert_one(data)


    return Response(status=200)
    # END CODE HERE


@app.route("/content-based-filtering", methods=["POST"])
def content_based_filtering():
    # BEGIN CODE HERE
    # Verify data integrity
    def get_type(value):
        if isinstance(value, dict):
            return {key: get_type(value[key]) for key in value}
        else:
            return str(type(value))
    
    # Calculate cosine similarity
    def cosine_similarity(v1, v2):
        dp = sum([a * b for a, b in zip(v1, v2)])
        m1 = sum([a ** 2 for a in v1]) ** 0.5
        m2 = sum([b ** 2 for b in v2]) ** 0.5
        return dp/(m1*m2)

    expected_schema = {
        "id"                :"",
        "name"              :"",
        "production_year"   :0,
        "price"             :0,
        "color"             :0,
        "size"              :0
    }

    # Getting json from POST
    data = request.get_json()   

    # If the data doesn't match the schema, return an error
    if get_type(data) != get_type(expected_schema):
        return Response("{'error':'Unexpected data syntax'}", status=406, mimetype='application/json')
    
    # Access the database collection
    products = mongo.db.products
    
    results = []
    for product in products.find():
        if cosine_similarity(list(product.values())[3:],list(data.values())[2:]) > 0.7:
            results.append(product['name'])

    return results
    # END CODE HERE


@app.route("/crawler", methods=["GET"])
def crawler():
    # BEGIN CODE HERE
    
    # Parse request parameter 
    semester = request.args.get('semester',type=int)
    
    # Define the path of the chromedriver
    CHROMEDRIVER_PATH = "C:\\Users\\anto\\Desktop\\webdriver\\chromedriver.exe"
    driver = webdriver.Chrome(executable_path=CHROMEDRIVER_PATH)

    # Navigate to the URL 
    url = f'https://qa.auth.gr/el/x/studyguide/600000438/current'
    driver.get(url)

    # Find the table element with the given semester parameter, that contains the subjects
    table = driver.find_element(By.ID,f'exam{semester}')

    # Extract the rows from the table
    rows = table.find_elements(By.TAG_NAME,'tr')

    # Create an empty list to store the subjects
    subjects = []

    # Iterate over the rows in the table, starting from the second row (skipping the header row)
    for row in rows[1:]:
        # Get the cells of the row
        cells = row.find_elements(By.TAG_NAME,('td'))

        # Extract the subject title from the second column
        subject_title=cells[1].text

        # Add the subject title to the list of subjects
        subjects.append(subject_title)

    # Close the ChromeDriver instance
    driver.quit()

    # Return the list of subjects as a JSON response
    return jsonify(subjects)
    # END CODE HERE
