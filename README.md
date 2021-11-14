# encrypting.host Uploader

This is a command line tool to upload files to encrypting.host on the command line.

## Usage

First, you need to create a config file. For Windows, the path is `%USERPROFILE%\.ehconfig.json`. (The `%USERPROFILE% environment variable points to your user directory, e.g. `C:\Users\sarah\`.) For macOS and Linux, it's `~/.ehconfig.json`. It should look like this:

```json
{
    "user_key": "",
    "url_style": "query",
    "domains": [
        "encrypting.host",
        "sharex.host"
    ]
}

```

Then, you can upload a file with `eh-uploader <file name>`.

## Installation

### Windows

Please download the latest release from the [Releases tab](https://github.com/encryptinghost/eh-uploader/releases). Extract the files to a folder somewhere called `eh-uploader`. Take note of where this folder is. As an example, we'll use `C:\Users\sarah\eh-uploader`. Take care to change your profile name if you use this path.

Next, we should put this folder in the Windows PATH. Open the Windows settings and go to `System` > `Advanced system settings` > `Environment Variables...`. In the bottom `System variables` category, scroll down until you find the environment variable called `Path`. Here, click on `New` and enter the path you noted above, in this case `C:\Users\sarah\eh-uploader`. That should be it. To test if you've done everything correctly, create the config, open a terminal and try to upload a file. You should be able to run the program with `eh-uploader <file name>`.