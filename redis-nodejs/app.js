import express from "express";
import cors from "cors";
import axios from "axios";
import {createClient} from "redis";

async function server_start(){
const app=express();

const client=await createClient().on("error",(err)=>{
    console.log(
        "redis client"
    )
}).connect();

app.use(cors());
app.get("/photo/:id",async (req,res)=>{
     const ids=req.params.id
     const data=await client.get(ids.toString());
     if(data!=null){
        console.log("cache hit");
         return res.json(JSON.parse(data));

     }
     else{
     const response=await axios.get("https://jsonplaceholder.typicode.com/photos",
        {
            params:{
                id:ids
            }
        }
     )
    console.log(response.data)
    console.log("cache miss");
    console.log(JSON.stringify(response.data));
    client.setEx(ids.toString(),3600,JSON.stringify(response.data));
    return res.json(response.data);
     }

   
})

app.listen(3000,()=>{
    console.log("port running on port 3000")
})
}
server_start();