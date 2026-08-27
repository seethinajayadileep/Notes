import  { devices,type PlaywrightTestConfig } from "@playwright/test";
const config: PlaywrightTestConfig={
  testMatch:["pom/addToCart.test.ts"],
  
  use:{
    baseURL: "https://ecommerce-playground.lambdatest.io/",
    headless:false,
    screenshot:"only-on-failure",
    video:"retain-on-failure"
  },
  reporter:[["dot"],["json", {
    outputFile: "jsonReports/jsonreport.json"
  }],["html",{
    open:"always"
  }]],
    projects: [
    {
      name: "chromium",
      use: {
        browserName: "chromium"
      }
    },
    {
      name:"chrome",
      use:{
        ...devices["Desktop Chrome"]
      }
    }
  ]
};
export default config