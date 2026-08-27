# Azure DevOps Pipeline – Complete Notes

## 1. Introduction

Azure DevOps Pipeline is a **CI/CD service** that automates:

- **Building** your code
- **Testing** automatically
- **Deploying** applications

It ensures **faster, consistent, and repeatable deployments**.

---

## 2. Key Terminology

| Term           | Meaning |
|----------------|---------|
| Pipeline       | Automated workflow to build, test, deploy |
| Agent          | Machine (VM or physical) that runs the pipeline jobs |
| Job            | A collection of steps executed on an agent |
| Step / Task    | Individual commands or actions (e.g., build, test, publish) |
| Artifact       | Output of a build (e.g., binaries, zip files, NuGet packages) |
| Trigger        | Event that starts the pipeline (commit, PR, schedule) |
| Stage          | Logical grouping of jobs (Build, Test, Deploy) |
| Variable       | Reusable parameter in pipeline for flexibility |

---

## 3. Why Build an Application?

1. **Compile Code** → Converts source files into executable files.
2. **Run Tests** → Validates functionality automatically.
3. **Package Artifacts** → Prepares outputs for deployment.
4. **Continuous Integration** → Detects errors early.
5. **Version Control** → Keeps track of builds for traceability.

---

## 4. Azure DevOps Pipeline Types

1. **Build Pipeline (CI)** – Creates artifacts from code.
2. **Release Pipeline (CD)** – Deploys artifacts to environments.
3. **Multi-stage Pipeline** – Combines Build + Deploy in a single YAML.

---

## 5. Pipeline Agents

- **Hosted Agents** → Azure provides ready-to-use agents: `windows-latest`, `ubuntu-latest`.
- **Self-hosted Agents** → Use your own machine to run pipelines.
- Agents execute **jobs**, which consist of multiple steps.

---

## 6. Pipeline YAML Structure

### Example: ASP.NET Build Pipeline

```yaml
trigger:
  branches:
    include:
      - Develop
      - release-*
    exclude:
      - main
      - release-bharath

paths:
  include:
    - HDFCLoans/HDFCLoans/Pages/*

pr:
  branches:
    include:
      - Develop

schedules:
  - cron: "*/15 * * * *"
    displayName: "Run every 15 minutes"
    branches:
      include:
        - Develop

pool:
  vmImage: 'windows-latest'

variables:
  solution: '**/*.sln'
  buildPlatform: 'Any CPU'
  buildConfiguration: 'Release'

steps:
- task: NuGetToolInstaller@1

- task: NuGetCommand@2
  inputs:
    restoreSolution: '$(solution)'

- task: VSBuild@1
  inputs:
    solution: '$(solution)'
    msbuildArgs: '/p:DeployOnBuild=true /p:WebPublishMethod=Package /p:PackageAsSingleFile=true /p:SkipInvalidConfigurations=true /p:PackageLocation="$(build.artifactStagingDirectory)"'
    platform: '$(buildPlatform)'
    configuration: '$(buildConfiguration)'

- task: VSTest@2
  inputs:
    platform: '$(buildPlatform)'
    configuration: '$(buildConfiguration)'

- task: PublishBuildArtifacts@1
  inputs:
    PathtoPublish: '$(Build.ArtifactStagingDirectory)'
    ArtifactName: 'drop'
    publishLocation: 'Container'
```

---

## 7. YAML Concepts Explained

### 7.1 Triggers

- **trigger** → Run pipeline automatically on branch commits.
- **pr** → Run pipeline on Pull Request creation.
- **schedules** → Cron-based pipeline runs (e.g., every 15 mins).

### 7.2 Pool

- `vmImage` → Specifies hosted agent OS.
- Example: `windows-latest` or `ubuntu-latest`.

### 7.3 Variables

- Reusable values across the pipeline.
- Example: `$(buildConfiguration)` or `$(solution)`.

### 7.4 Steps / Tasks

- Each task performs a specific action.
- **NuGetToolInstaller** → Ensures NuGet CLI available.
- **NuGetCommand restore** → Restores dependencies.
- **VSBuild** → Builds the solution.
- **VSTest** → Runs unit tests.
- **PublishBuildArtifacts** → Publishes output for release.

---

## 8. Artifacts

- **Definition**: Files produced by the build (DLLs, EXE, ZIP, NuGet packages).
- **Purpose**:
  1. Reuse in deployment.
  2. Version control of build outputs.
  3. Enable **Continuous Deployment**.
- **Publishing Artifacts**: Use `PublishBuildArtifacts@1` task.

---

## 9. Multi-stage Pipelines

- Combine **Build + Test + Deploy** in single YAML.
- Example:

```yaml
stages:
- stage: Build
  jobs:
  - job: BuildJob
    steps:
    - script: echo Building

- stage: Deploy
  jobs:
  - job: DeployJob
    steps:
    - script: echo Deploying
```

---

## 10. Best Practices

1. Use **variables** for configuration values.
2. Use **stages** for logical separation.
3. Keep **pipeline YAML** in source control.
4. Run **tests automatically** to catch errors early.
5. Keep **artifacts** organized by name and version.
6. Use **cron triggers** for nightly or frequent builds.

---

## 11. Summary

- Azure DevOps Pipelines automate **build, test, and deployment**.
- **Agents** run jobs; **steps** perform tasks.
- **Artifacts** are build outputs for deployment.
- **Triggers** start pipelines automatically or on schedules.
- Multi-stage pipelines allow **CI + CD** in one workflow.

---

## 12. References

- [Azure DevOps Pipelines for ASP.NET](https://docs.microsoft.com/azure/devops/pipelines/apps/aspnet/build-aspnet-4)
- [Pipeline YAML schema](https://docs.microsoft.com/azure/devops/pipelines/yaml-schema)

