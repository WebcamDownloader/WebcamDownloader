# CLI usage

The app can be used with a GUI (when launched with no parameters) or CLI (when launched with parameters).

> The exception are CLI only builds for Linux which can only be used from CLI and don't require X server

## Commands

The list of commands follows. Note that the `download` command is a work in progress.

- `help`
    - Prints either generic help (with no arguments) or a command related help
    - Arguments:
        - `command` *optional* - if present a help for other commands is provided
- `hosts`
    - Prints list of hosts
- `add`
    - Adds/updates model in the internal database
    - Arguments:
        - `host` **required** - a name of the webcam host (taken from the `hosts` command)
        - `model-name` **required** - the name of the model
    - Options:
        - `--autodownload` - if present the model will be downloaded automatically if automatic downloads are enabled
- `models`
    - Prints list of models in the internal database
    - Options:
        - `--format` - the output format, can be either `json` or `text`, defaults to `text`
- `remove`
    - Removes a model from internal database
    - Arguments:
        - `host` *optional* - if the host is present, only model matching the name **and** host will be deleted
        otherwise all models with the same name will be deleted
        - `model-name` **required** - the name of the model to delete
    - Options:
        - `--silentfail` - if the option is present, exits with status 0 in case the model is not found in internal
        database
- `settings`
    - Sets or gets various app settings
    - Arguments:
        - `setting-name` **required** - the name of the setting to get or set
            - Allowed values:
                - `download-dir` - the directory where shows will be downloaded to
                - `auto-downloads` **GUI only** - whether to enable or disable autodownloads in GUI (`true` or `false`)
                - `new-version-check` **GUI only** - whether to enable or disable checking for new version in GUI
                  (`true` or `false`)
            - Settings marked as **GUI only** are not available in CLI only version of the app
        - `setting-value` *optional* - if this argument is present the setting is set to the value, if it's not present
        the current value gets printed instead, the command returns no output if this argument is present
- `download`
    - **unfinished**
    - Arguments:
        - `models` *optional* - space separated list of models to be downloaded, if the arguments are not present
        the default action is to download all models that are set to autodownload
    - Caveats:
        - In the current implementation the models don't resume download after going offline
        - In the current implementation nly models that are online at the time this command is run are downloaded
        - *All of these caveats will be fixed in future versions*
    