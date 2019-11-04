const Alexa = require('ask-sdk-core');

const LaunchRequestHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'LaunchRequest';
    },
    handle(handlerInput) {
        const speakOutput = `${WELCOME_MESSAGE} ${GET_MANUAL_MESSAGE} ${FALLBACK_REPROMPT}`;
        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(FALLBACK_REPROMPT)
            .getResponse();
    }
};

const GetManualHandler = {
    canHandle(handlerInput) {
      const request = handlerInput.requestEnvelope.request;
      return request.type === 'IntentRequest'
          && request.intent.name === 'GetManualIntent';
    },
    handle(handlerInput) {
        return handlerInput.responseBuilder
            .speak(`${GET_MANUAL_MESSAGE} ${FALLBACK_REPROMPT}`)
            .reprompt(HELP_REPROMPT)
            .getResponse();
    },
  };

  const GetLightsHandler = {
    canHandle(handlerInput) {
      const request = handlerInput.requestEnvelope.request;
      return request.type === 'IntentRequest'
          && request.intent.name === 'GetLightsIntent';
    },
    handle(handlerInput) {
        return handlerInput.responseBuilder
            .speak(`${GET_LIGHTS_MESSAGE} ${FALLBACK_REPROMPT}`)
            .reprompt(HELP_REPROMPT)
            .getResponse();
    },
  };

const HelpIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.HelpIntent';
    },
    handle(handlerInput) {
        const speakOutput = `${HELP_MESSAGE}`;

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(FALLBACK_REPROMPT)
            .getResponse();
    }
};
const CancelAndStopIntentHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest'
            && (Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.CancelIntent'
                || Alexa.getIntentName(handlerInput.requestEnvelope) === 'AMAZON.StopIntent');
    },
    handle(handlerInput) {
        const speakOutput = `${STOP_MESSAGE}`;
        return handlerInput.responseBuilder
            .speak(speakOutput)
            .getResponse();
    }
};
const SessionEndedRequestHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'SessionEndedRequest';
    },
    handle(handlerInput) {
        return handlerInput.responseBuilder.getResponse();
    }
};

const IntentReflectorHandler = {
    canHandle(handlerInput) {
        return Alexa.getRequestType(handlerInput.requestEnvelope) === 'IntentRequest';
    },
    handle(handlerInput) {
        const intentName = Alexa.getIntentName(handlerInput.requestEnvelope);
        const speakOutput = `You just triggered ${intentName}`;

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .getResponse();
    }
};

const ErrorHandler = {
    canHandle() {
        return true;
    },
    handle(handlerInput, error) {
        console.log(`~~~~ Error handled: ${error.stack}`);
        const speakOutput = `${ERROR_MESSAGE}`;

        return handlerInput.responseBuilder
            .speak(speakOutput)
            .reprompt(speakOutput)
            .getResponse();
    }
};

const WELCOME_MESSAGE = 'Hola, bienvenido al manual del proyecto Acnes: Esta es una guia rapida de los comandos que puedes utilizar para controlar las luces del edificio.';
const GET_MANUAL_MESSAGE = 'Para formular un comando, después de decir Alexa, tienes que decir si quieres encender o apagar y qué es lo que quieres que se encienda o apague, un ejemplo es: Alexa, enciende la luz del salon uno.';
const GET_LIGHTS_MESSAGE = 'Los dispositivos que existen para encenderse o apagarse son: La luz del salon uno, la luz del salon dos, la luz del salon tres, las luces de los salones, las luces del pasillo, las teles, las luces, la luz del laboratorio oriente, la luz del laboratorio poniente, la luz de los cubiculos, la luz de celdas, o bien puedes pedir que se enciende o se apague todo';
const HELP_MESSAGE = 'Puedes decirme que te repita la guia, que te mencione las luces que estan disponibles para controlar, o, puedes decir salir del manual... ¿Con qué puedo ayudarte?';
const HELP_REPROMPT = '¿Con qué puedo ayudarte?';
const FALLBACK_MESSAGE = 'La este manual no puede ayudarte con eso. Te puede ayudar proporcionandote una guia rapida de los comandos que puedes utilizar para controlar las luces del edificio';
const FALLBACK_REPROMPT = '¿Con qué más puedo ayudarte?';
const STOP_MESSAGE = '¡Hasta la próxima!';
const ERROR_MESSAGE = 'Lo siento, ha ocurrido un error';

exports.handler = Alexa.SkillBuilders.custom()
    .addRequestHandlers(
        LaunchRequestHandler,
        GetManualHandler,
        GetLightsHandler,
        HelpIntentHandler,
        CancelAndStopIntentHandler,
        SessionEndedRequestHandler,
        IntentReflectorHandler,
    )
    .addErrorHandlers(
        ErrorHandler,
    )
    .lambda();
