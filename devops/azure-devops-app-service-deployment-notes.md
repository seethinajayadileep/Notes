# Azure DevOps YAML Pipeline → Deploy .NET App to Azure App Service

> Student-friendly notes on connecting an Azure DevOps pipeline to Azure using a **Service Connection** and deploying a **.NET 10 LTS** web app to **Azure App Service**.

---

## Table of Contents

1. [Overview – What & Why](#1-overview--what--why)
2. [The Full Deployment Flow](#2-the-full-deployment-flow)
3. [Important Concepts (Glossary)](#3-important-concepts-glossary)
4. [Service Connection – Two Methods](#4-service-connection--two-methods)
5. [Manual vs Automatic – Comparison Table](#5-manual-vs-automatic--comparison-table)
6. [YAML Task Explained Line by Line](#6-yaml-task-explained-line-by-line)
7. [Quick Recap / Cheat Sheet](#7-quick-recap--cheat-sheet)

---

## 1. Overview – What & Why

### What is the goal?
Take the code you wrote on your machine, push it to a repository, and have it **automatically built and deployed** to a live website running on Azure — without you manually copying files to the server.

### Why do we need Azure DevOps + Azure App Service connection?
- **Azure DevOps** is the *factory*: it builds your code, packages it, and ships it.
- **Azure App Service** is the *destination*: a managed place on Azure where your web app actually runs.
- For the factory to ship to the destination, it needs **permission and trust**. That trust is set up using a **Service Connection**.

### What problem does this solve?
Without this setup, every release means: build manually → zip manually → log into the server → upload → restart → hope nothing broke.

With this setup, the process becomes:

```
git push  ──►  pipeline builds & deploys automatically  ──►  live site updated
```

This gives you **automation, repeatability, fewer mistakes, and faster releases** (the core idea of CI/CD).

---

## 2. The Full Deployment Flow

Think of it as a relay race — code is passed from one stage to the next:

```
┌─────────────┐   ┌──────────────────┐   ┌─────────────────┐   ┌───────────────────┐   ┌──────────────────┐   ┌─────────────┐
│ 1. Code in  │ ► │ 2. Azure DevOps  │ ► │ 3. Build &      │ ► │ 4. Azure Service  │ ► │ 5. App Service   │ ► │ 6. Web App  │
│ Repository  │   │    Pipeline      │   │    Zip Package  │   │    Connection     │   │    Deploy Task   │   │ (Live Site) │
└─────────────┘   └──────────────────┘   └─────────────────┘   └───────────────────┘   └──────────────────┘   └─────────────┘
```

**Step-by-step:**

1. **Code in Repository** – Your `.NET` source code lives in a Git repo (Azure Repos or GitHub).
2. **Azure DevOps Pipeline** – Triggered (often on every push). It restores packages, compiles, and tests the code.
3. **Build Artifact / Zip Package** – The compiled output is bundled into a `.zip` file. This deployable bundle is the *artifact*.
4. **Azure Service Connection** – The pipeline uses the saved connection to **prove its identity** to Azure and gain permission to deploy.
5. **Azure App Service Deploy Task** – The task takes the `.zip` and pushes it to the target Web App.
6. **Deployment to Web App** – Azure unpacks the zip, swaps in the new version, and your site is live.

> 💡 **Mental model:** Build = *make the package*. Deploy = *send the package*. The Service Connection = *the key that unlocks the door*.

---

## 3. Important Concepts (Glossary)

| Concept | Simple Explanation |
|---|---|
| **Azure DevOps Pipeline** | An automated workflow that builds, tests, and deploys your code. The "assembly line." |
| **YAML Pipeline** | The pipeline defined as code in a `.yml` file stored in your repo. Versioned, reviewable, repeatable. |
| **Azure App Service** | A fully managed hosting service for web apps & APIs. You bring code; Azure handles servers, patching, scaling. |
| **App Service Plan** | Defines the **compute resources** (CPU, RAM, region, pricing tier) your App Service runs on. Like the "engine" the app sits on. Multiple apps can share one plan. |
| **Resource Group** | A logical folder that groups related Azure resources (web app, plan, database) so you manage/delete them together. |
| **Microsoft Entra ID** | Azure's identity service (formerly *Azure Active Directory*). Manages users, apps, and who-can-access-what. |
| **App Registration** | Registering your pipeline as an "application identity" inside Entra ID so it can authenticate to Azure. |
| **Service Principal** | The actual **identity/account** created for that app. Think of it as a "robot user" the pipeline logs in as. |
| **Client ID** | The unique **username** of the service principal (App ID). |
| **Tenant ID** | The unique ID of your **organization's** Entra directory. |
| **Subscription ID** | The unique ID of the Azure **subscription** that pays for and contains your resources. |
| **Client Secret** | The **password** for the service principal. Keep it secret; it expires and must be rotated. |
| **Role Assignment** | Granting an identity permission to do things on a resource (RBAC – Role-Based Access Control). |
| **Contributor role** | Can **create and manage** resources, but **cannot** grant access to others. ✅ Usually enough for deployments. |
| **Owner role** | Full control **including** assigning roles to others. More power than deployments need — use sparingly. |
| **Azure Resource Manager (ARM) Service Connection** | The bridge in Azure DevOps that stores the service principal credentials so pipelines can talk to Azure securely. |

> 🔑 **Three IDs to remember:**
> - **Client ID** = *who* is logging in (the robot user)
> - **Tenant ID** = *which organization* it belongs to
> - **Subscription ID** = *which bill/account* the resources sit in

---

## 4. Service Connection – Two Methods

A **Service Connection** lets the pipeline authenticate to Azure. There are two ways to create it.

### A. Manual Service Connection Method

You create the identity yourself in Entra ID, then plug the details into Azure DevOps. More steps, but full control.

1. **Create App Registration** in Microsoft Entra ID
   → Entra ID → *App registrations* → *New registration* → name it (e.g. `devops-deploy-sp`).
2. **Generate a Client Secret**
   → Open the app → *Certificates & secrets* → *New client secret* → **copy the value immediately** (shown only once).
3. **Copy the four values** you'll need:
   - Client ID
   - Tenant ID
   - Subscription ID
   - Client Secret
4. **Add a Role Assignment** in the Azure subscription / resource group
   → Resource Group → *Access control (IAM)* → *Add role assignment* → choose **Contributor** → assign it to your app registration.
5. **Create the Service Connection in Azure DevOps**
   → Project Settings → *Service connections* → *New* → *Azure Resource Manager* → **Service principal (manual)** → paste the four values.
6. **Verify and Save**
   → Click **Verify** to confirm credentials work → name the connection → save.

> ⚠️ Because *you* created the secret, *you* are responsible for **rotating it before it expires**.

### B. Automatic Service Connection Method

Azure DevOps does the heavy lifting — it creates and configures the service principal for you behind the scenes.

1. **Azure DevOps automatically creates/configures the service principal** when you authenticate.
2. **Select the Subscription** from a dropdown (you log in with your Azure account).
3. **Select the Resource Group** (optionally scope it to one group).
4. **Authorize the connection** — Azure DevOps wires up the identity and role assignment automatically.
5. **Use it in pipeline YAML** by referencing its name in `azureSubscription:`.

> ✅ Fewer steps, fewer mistakes — best when you have permission to create identities in Entra ID.

---

## 5. Manual vs Automatic – Comparison Table

| Aspect | 🛠️ Manual Connection | ⚡ Automatic Connection |
|---|---|---|
| **Ease of setup** | Harder — many manual steps, easy to mistype an ID | Easy — guided wizard, mostly automatic |
| **Security control** | High — you control the exact identity, scope & secret | Moderate — Azure DevOps decides defaults |
| **When to use** | Restricted environments; identity is pre-created by an admin; you need precise scoping | Quick setup; you have rights to create app registrations & assign roles |
| **Required permissions** | Someone must already have Entra ID + role-assignment rights to create the SP for you | You need rights to create app registrations **and** assign roles |
| **Common mistakes** | Wrong/expired secret, forgetting role assignment, mixing up Client vs Tenant vs Subscription ID, secret not copied at creation | Picking the wrong subscription, insufficient permissions to auto-create the SP, over-broad scope |

> 🏢 **Rule of thumb:** In a tightly governed company, **Manual** (an admin pre-creates the identity). For your own learning/projects, **Automatic** is fastest.

---

## 6. YAML Task Explained Line by Line

```yaml
- task: AzureRmWebAppDeployment@5
  inputs:
    ConnectionType: 'AzureRM'
    azureSubscription: 'SERVICE_CONNECTION_NAME'
    appType: 'webApp'
    WebAppName: 'WEB_APP_NAME'
    packageForLinux: '$(Build.ArtifactStagingDirectory)/**/*.zip'
```

| Line | Meaning |
|---|---|
| `task: AzureRmWebAppDeployment@5` | Use the **Azure App Service Deploy** task, version **5**. This is the built-in task that ships your app to App Service. |
| `ConnectionType: 'AzureRM'` | Use **Azure Resource Manager** authentication — i.e. deploy via the service connection (not FTP/publish profile). |
| `azureSubscription: 'SERVICE_CONNECTION_NAME'` | The **name of your Service Connection**. This is how the task authenticates to Azure. Replace with your connection's actual name. |
| `appType: 'webApp'` | The kind of App Service target. `webApp` = a standard web app (use `webAppLinux` for Linux-specific apps). |
| `WebAppName: 'WEB_APP_NAME'` | The **exact name** of the Web App in Azure to deploy into. Replace with your real app name. |
| `packageForLinux: '$(Build.ArtifactStagingDirectory)/**/*.zip'` | The path to the deployable **zip package**. `$(Build.ArtifactStagingDirectory)` is a built-in variable pointing to where build output is staged; `**/*.zip` means "find any zip in any subfolder." |

> 📦 **In plain English:** *"Using the AzureRM service connection named X, take the zip file from my build folder, and deploy it into the Web App named Y."*

---

## 7. Quick Recap / Cheat Sheet

- **Goal:** Push code → pipeline builds & deploys automatically → live site on App Service.
- **Service Connection = trust bridge** between Azure DevOps and Azure.
- **Service Principal = robot user**; **Client ID** = its username, **Client Secret** = its password.
- **Three IDs:** Client (who) · Tenant (which org) · Subscription (which bill).
- **Contributor** role is usually enough; **Owner** is overkill for deployments.
- **Manual** = full control, more steps; **Automatic** = fast, fewer steps.
- **YAML deploy task** = service connection + web app name + zip path.
- **Resource Group** holds resources; **App Service Plan** provides the compute the Web App runs on.

---

