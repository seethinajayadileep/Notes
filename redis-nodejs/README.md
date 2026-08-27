# Redis Caching in Node.js with Express

This project is a simple practical implementation of **Redis caching** in **Node.js** using **Express**, **Axios**, and **Redis**.

It fetches photo data from the public API:

https://jsonplaceholder.typicode.com/photos

Before calling the external API, the server first checks whether the requested data is already stored in Redis.

- If data is present in Redis, it returns the cached response (**cache hit**)
- If data is not present, it fetches data from the API, stores it in Redis for **1 hour**, and then returns the response (**cache miss**)

---

## Features

- Node.js + Express backend
- Redis caching
- Axios for API requests
- CORS enabled
- Cache expiration using TTL
- Simple practical project for learning Redis

---

## Technologies Used

- Node.js
- Express.js
- Redis
- Axios
- CORS

---

## Project Working

### Route

```bash
/photo/:id
Flow
User sends request to /photo/:id
Server checks Redis using the photo id as key
If data exists in Redis:
prints cache hit
returns cached data
If data does not exist:
fetches data from JSONPlaceholder API
stores data in Redis for 3600 seconds
prints cache miss
returns API response
Code
import express from "express";
import cors from "cors";
import axios from "axios";
import { createClient } from "redis";

async function server_start() {
    const app = express();

    const client = await createClient()
        .on("error", (err) => {
            console.log("Redis Client Error:", err);
        })
        .connect();

    app.use(cors());

    app.get("/photo/:id", async (req, res) => {
        const ids = req.params.id;

        try {
            const data = await client.get(ids.toString());

            if (data != null) {
                console.log("cache hit");
                return res.json(JSON.parse(data));
            } else {
                const response = await axios.get(
                    "https://jsonplaceholder.typicode.com/photos",
                    {
                        params: {
                            id: ids
                        }
                    }
                );

                console.log("cache miss");

                await client.setEx(
                    ids.toString(),
                    3600,
                    JSON.stringify(response.data)
                );

                return res.json(response.data);
            }
        } catch (error) {
            console.log("Error:", error.message);
            return res.status(500).json({
                message: "Internal Server Error"
            });
        }
    });

    app.listen(3000, () => {
        console.log("Server running on port 3000");
    });
}

server_start();
Installation Steps
1. Clone the repository
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
2. Install dependencies
npm install
3. Install required packages
npm install express cors axios redis
4. Start Redis server
redis-server
5. Run the project
node index.js
package.json

Use this if you are using ES modules:

{
  "name": "redis-practical",
  "version": "1.0.0",
  "description": "Redis caching practical in Node.js",
  "main": "index.js",
  "type": "module",
  "scripts": {
    "start": "node index.js"
  },
  "dependencies": {
    "axios": "^1.6.0",
    "cors": "^2.8.5",
    "express": "^4.18.2",
    "redis": "^4.6.7"
  }
}
Example Request

Open this in browser or Postman:

http://localhost:3000/photo/1
Expected Output
First Request
Data comes from API
Terminal prints:
cache miss
Second Request for same ID
Data comes from Redis
Terminal prints:
cache hit
Redis Method Used
get()

Used to retrieve cached data from Redis.

const data = await client.get(ids.toString());
setEx()

Used to store data in Redis with expiration time.

await client.setEx(ids.toString(), 3600, JSON.stringify(response.data));
ids.toString() → Redis key
3600 → expiration time in seconds
JSON.stringify(response.data) → value stored in Redis
What I Learned

Through this practical, I learned:

how Redis works as an in-memory cache
how to connect Redis with Node.js
how to reduce repeated API calls
how to improve performance using caching
how TTL works in Redis using setEx()
Future Improvements

This project can be improved by adding:

environment variables
better logging
custom error handling
multiple API routes
cache invalidation
Docker support
Author

Practical notes for learning Redis in Node.js with Express.


For your repo, rename `your-username` and `your-repo-name` before pasting.

I can also give you:
`index.js + package.json + README.md` together in one single