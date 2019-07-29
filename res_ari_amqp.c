/*
 * Asterisk -- An open source telephony toolkit.
 *
 * Copyright (C) 2019 The Wazo Authors  (see the AUTHORS file)
 *
 * Nicolaos Ballas
 *
 * See http://www.asterisk.org for more information about
 * the Asterisk project. Please do not directly contact
 * any of the maintainers of this project for assistance;
 * the project provides a web site, mailing lists and IRC
 * channels for your use.
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!!!                               DO NOT EDIT                        !!!!!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * This file is generated by a mustache template. Please see the original
 * template in rest-api-templates/res_ari_resource.c.mustache
 */

/*! \file
 *
 * \brief AMQP resources
 *
 * \author Nicolaos Ballas
 */

/*** MODULEINFO
	<depend type="module">res_ari</depend>
	<depend type="module">res_ari_model</depend>
	<depend type="module">res_stasis</depend>
	<support_level>core</support_level>
 ***/

#include "asterisk.h"

#include "asterisk/app.h"
#include "asterisk/module.h"
#include "asterisk/stasis_app.h"
#include "resource_amqp.h"
#if defined(AST_DEVMODE)
#include "ari/ari_model_validators.h"
#endif

#define MAX_VALS 128

/*!
 * \brief Parameter parsing callback for /amqp/{applicationName}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_amqp_stasis_subscribe_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_json *body, struct ast_ari_response *response)
{
	struct ast_ari_amqp_stasis_subscribe_args args = {};
	struct ast_variable *i;
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "applicationName") == 0) {
			args.application_name = (i->value);
		} else
		{}
	}
	ast_ari_amqp_stasis_subscribe(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
	case 400: /* Bad request. */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_application(
				response->message);
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /amqp/{applicationName}\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /amqp/{applicationName}\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}
/*!
 * \brief Parameter parsing callback for /amqp/{applicationName}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_amqp_stasis_unsubscribe_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_json *body, struct ast_ari_response *response)
{
	struct ast_ari_amqp_stasis_unsubscribe_args args = {};
	struct ast_variable *i;
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "applicationName") == 0) {
			args.application_name = (i->value);
		} else
		{}
	}
	ast_ari_amqp_stasis_unsubscribe(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
	case 400: /* Bad request. */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_application(
				response->message);
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /amqp/{applicationName}\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /amqp/{applicationName}\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}

/*! \brief REST handler for /api-docs/amqp.json */
static struct stasis_rest_handlers amqp_applicationName = {
	.path_segment = "applicationName",
	.is_wildcard = 1,
	.callbacks = {
		[AST_HTTP_POST] = ast_ari_amqp_stasis_subscribe_cb,
		[AST_HTTP_DELETE] = ast_ari_amqp_stasis_unsubscribe_cb,
	},
	.num_children = 0,
	.children = {  }
};
/*! \brief REST handler for /api-docs/amqp.json */
static struct stasis_rest_handlers amqp = {
	.path_segment = "amqp",
	.callbacks = {
	},
	.num_children = 1,
	.children = { &amqp_applicationName, }
};

static int unload_module(void)
{
	ast_ari_remove_handler(&amqp);
	return 0;
}

static int load_module(void)
{
	int res = 0;


	res |= ast_ari_add_handler(&amqp);
	if (res) {
		unload_module();
		return AST_MODULE_LOAD_DECLINE;
	}

	return AST_MODULE_LOAD_SUCCESS;
}

AST_MODULE_INFO(ASTERISK_GPL_KEY, AST_MODFLAG_DEFAULT, "RESTful API module - AMQP resources",
	.support_level = AST_MODULE_SUPPORT_CORE,
	.load = load_module,
	.unload = unload_module,
	.requires = "res_ari,res_ari_model,res_stasis_amqp",
);
