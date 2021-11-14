# encrypting.host Uploader

This is a command line tool to upload files to encrypting.host on the command line.

## Usage

First, you need to create a config file. For Windows, the path is `%USERPROFILE%\.ehconfig.json`. For macOS and Linux, it's `~/.ehconfig.json`. It should look like this:

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