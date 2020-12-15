import requests
import json
from pyspark.sql import SparkSession
from pyspark.sql import Row
from pyspark.sql.types import StringType, StructType, StructField
from pyspark.sql import functions as F


if __name__ == "__main__":

    spark = SparkSession \
        .builder \
        .appName("Python Spark SQL basic example") \
        .config("spark.some.config.option", "some-value") \
        .getOrCreate()

    def getDataFromApi():
        url = "http://144.202.34.148:3010/api/product"
        response = requests.get(url)
        return response.text


    data = getDataFromApi()
    data = data[11:]
    data = data[:-1] 
    print(data)
    json_rdd = spark.sparkContext.parallelize([data])
    df = spark.read.json(json_rdd)
    df.printSchema()
    result = df.select("temperatura").agg(F.min(df["temperatura"]), F.max(df["temperatura"]), F.avg(df["temperatura"]))
    result.show()
    spark.stop()
